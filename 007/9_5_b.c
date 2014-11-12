#include <stdio.h>
#include <stdlib.h>
#include "unweighted.h"

int main(int argc, char *argv[]){
  int vertex_num;
  int connection_num;
  int from, to;
  Info *table;
  Graph G;

  scanf("%d", &vertex_num);
  G = create_graph(vertex_num);
  scanf("%d", &connection_num);
  for (int i = 0; i < connection_num; i++){
    scanf("%d%d", &from, &to);
    connect_to(G, from, to);
  }
  scanf("%d", &from);
  table = unweighted(G, from);
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
