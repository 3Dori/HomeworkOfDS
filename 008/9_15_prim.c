#include <stdio.h>
#include <stdlib.h>
#include "prim.h"

int main(void){
  Graph G;
  Info *table;

  G = input_graph();
  table = prim(G);

  for (int i = 1; i <= G->vertex_num; i++){
    if (table[i].path != NOT_A_VERTEX)
      printf("%d--%d: %d\n", i, table[i].path, table[i].dist);
  }

  return 0;
}
