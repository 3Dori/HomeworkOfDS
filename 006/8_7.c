#include <stdlib.h>
#include <stdio.h>

typedef int *set;
typedef int elem_type;

set create( int size );
int find( set S, elem_type x1 );
int is_connected( set S, elem_type x1, elem_type x2 );
void connect( set S, elem_type x1, elem_type x2 );

int main( void ){
  int N;
  char ins;
  int c1, c2;
  set S;

  scanf( "%d", &N );
  S = create( N );
  getchar();
  while ( ( ins = getchar() ) != 'S' ){ // S: stop
    scanf( "%d%d", &c1, &c2 );
    getchar();
    if ( ins == 'I' )
      connect( S, c1, c2 );
    else if ( ins == 'C' ){
      if ( is_connected( S, c1, c2) )
	printf( "yes\n" );
      else
	printf( "no\n" );
    }
  }
  // print connected components
  if ( S[ 0 ] == 1 )
    printf( "The network is connected." );
  else
    printf( "There are %d components.", S[ 0 ] );

  return 0;
}

set create( int size ){
  set S;

  S = ( set )malloc( sizeof( elem_type ) * ( size + 1 ) );
  if ( S == NULL ){
    printf( "Out of space\n" );
    exit(1);
  }
  S[ 0 ] = size; // A subtle tactic: Use S[ 0 ] to record the number of connected components
  for ( int i = 1; i <= size; i++ )
    S[ i ] = -1; // S[ i ] is the negate of its size

  return S;
}

int find( set S, elem_type x1 ){
  // a non-recursive find routine
  int root;
  int parent;

  root = parent = x1;
  while ( S[ root ] > 0 ) // not root
    root = S[ root ];
  while ( x1 != root ){
    parent = S[ x1 ];
    S[ x1 ] = root;
    x1 = parent;
  }

  return root;
}

int is_connected( set S, elem_type x1, elem_type x2 ){
  return find( S, x1 ) == find( S, x2 );
}

void connect( set S, elem_type x1, elem_type x2 ){
  int root1, root2;
  // find their roots
  root1 = find( S, x1 );
  root2 = find( S, x2 );
  // check whether they are in the same set
  if ( root1 == root2 )
    return;
  else{ // union by size
    S[ 0 ]--; // decrease the number of connected components by 1
    if ( S[ root1 ] < S[ root2 ] ){ // x1 has larger size
      S[ root1 ] += S[ root2 ]; // increase the size
      S[ root2 ] = root1;
    }
    else{
      S[ root2 ] += S[ root1 ];
      S[ root1 ] = root2;
    }
  }
}
