#include <stdio.h>
#include <stdlib.h>
#include "dijkstra.h"

int main(int argc, char *argv[]){
  Graph G;
  Info *table;
  int vertex_num;
  int connection_num;
  int from, to, weight;

  scanf("%d", &vertex_num);    // input number of vertices in the graph
  G = create_graph(vertex_num);
  scanf("%d", &connection_num);    // input number of connections in the graph
  for (int i = 0; i < connection_num; i++){
    scanf("%d%d%d", &from, &to, &weight);    // input the from vertex, to vertex and weight of the edge
    connect_to(G, from, to, weight);
  }
  scanf("%d", &from);    // input the start of paths
  table = dijkstra(G, from);    // get the shortest path from the input vertex
  for (int i = 1; i <= vertex_num; i++){
    if (i != from){
      if (table[i].dist == INF)
	printf("No path from %d to %d\n", from, i);
      else{
	printf("To vertex %d: distance %d ", i, table[i].dist);
	print_path(table, i);
	putchar('\n');
      }
    }
  }

  dispose_graph(G);
  dispose_table(table);
}
