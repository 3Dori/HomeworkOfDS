#ifndef __DISJSET_H__
#define __DISJSET_H__
#include <stdlib.h>
typedef int *Set;

Set initialize_set(int size);
void union_set(Set S, int a, int b);
int is_connected(Set S, int a, int b);
int find(Set S, int a);

Set initialize_set(int size){
  Set S;

  S = (Set)malloc(sizeof(int) * (size + 1));
  for (int i = 1; i <= size; i++){
    S[i] = -1;    // if i is a root, its value is the negation of its set size
  }

  return S;
}

void dispose_set(Set S){
  if (S != NULL)
    free(S);
}

int find(Set S, int a){
  int root, trail;

  for (root = a; S[root] > 0; root = S[root]);    // find the root
  for (; a != root; a = trail){    // path compression
    trail = S[a];
    S[a] = root;
  }

  return root;
}

int is_connected(Set S, int a, int b){
  int roota, rootb;

  roota = find(S, a);
  rootb = find(S, b);

  return roota == rootb;
}

void union_set(Set S, int a, int b){
  int roota, rootb;

  roota = find(S, a);
  rootb = find(S, b);
  if (roota == rootb)
    return;
  else if (roota > rootb){  // size[a] < size[b], let b be the root of a
    S[rootb] += S[roota];
    S[roota] = rootb;
  }
  else{
    S[roota] += S[rootb];
    S[rootb] = roota;
  }
}

#endif
