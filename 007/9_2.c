#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

void test(void);
int main(void){
  test();

  return 0;
}

void test(void){
  int graph_size; // the size of graph
  int connect_cases; // number of connections in the graph
  int v1, v2;
  Graph G;

  scanf("%d%d", &graph_size, &connect_cases);
  G = create_graph(graph_size);
  for (int i = 0; i < connect_cases; i++){
    scanf("%d%d", &v1, &v2);
    connect_vertices(G, v1, v2);
  }
  topological_sort(G);
  dispose_graph(G);
}
