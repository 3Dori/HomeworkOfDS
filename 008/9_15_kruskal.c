#include <stdio.h>
#include <stdlib.h>
#include "kruskal.h"

void test(void){
  char ins;
  int a, b;
  Set S;

  S = initialize_set(10);
  for (;;){
    scanf("%c%d%d", &ins, &a, &b);
    getchar();
    switch (ins){
    case 'c': union_set(S, a, b); break;
    case 'f': printf("%d\n", is_connected(S, a, b)); break;
    default: exit(0);
    }
  }
}

int main(void){
  Graph G;
  Edge *result;

  //  test();

  G = input_graph();
  result = kruskal(G);

  for (int i = 0; i < G->vertex_num - 1; i++){
    printf("%d--%d: %d\n", result[i].from, result[i].to, result[i].length);
  }

  free(result);
  return 0;
}
