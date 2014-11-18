#ifndef __PRIM_H__
#define __PRIM_H__
#include "graph.h"
#define INF 10000
#define NOT_A_VERTEX 0
typedef struct info_record Info;
struct info_record{
  // table element
  int known;
  int dist;
  int path;
};

Info *prim(Graph G);

int find_shortest_unknown(Info *table, int size){
  // return the adjacent vertex of u with the shortest distance, still unknown
  // store the shortest distance in dist
  int v, min_weight;

  v = 0;
  min_weight = INF;
  for (int i = 1; i <= size; i++){
    if (table[i].dist < min_weight && !table[i].known){
      min_weight = table[i].dist;
      v = i;
    }
  }

  return v;
  /* found = 0; */
  /* min_weight = INF; */
  /* for (L = G->vertices[u]->next; L != NULL; L = L->next){ */
  /*   if (L->weight < min_weight && !table[L->index].known){ */
  /*     found = 1; */
  /*     v = L->index; */
  /*   } */
  /* } */

  /* if (found) */
  /*   return v; */
  /* else */
  /*   return 0; */
}

void update_dist(Graph G, Info *table, int u){
  List L;

  for (L = G->vertices[u]->next; L != NULL; L = L->next){
    if (L->weight < table[L->index].dist && !table[L->index].known){    // find a shorter path
      table[L->index].dist = L->weight;
      table[L->index].path = u;
    }
  }
}

Info *initialize_table(Graph G){
  Info *table;
  int u;

  table = (Info *)malloc(sizeof(Info) * (G->vertex_num + 1));
  for (int i = 1; i <= G->vertex_num; i++){
    table[i].known = 0;
    table[i].dist = INF;
    table[i].path = NOT_A_VERTEX;
  }

  u = 1;
  table[u].known = 1;
  table[u].dist = 0;

  return table;
}

Info *prim(Graph G){
  Info *table;
  int u, v;    // u is the vertex in the tree, while v isn't
  int tree_node_num, vertex_num;

  table = initialize_table(G);
  u = 1;
  tree_node_num = 1;
  vertex_num = G->vertex_num;
  while (tree_node_num < vertex_num){
    update_dist(G, table, u);
    v = find_shortest_unknown(table, G->vertex_num);
    if (!v){
      printf("No minimal spanning tree\n");
      exit(1);
    }
    table[v].known = 1;
    u = v;
    tree_node_num++;
  }

  return table;
}

void dispose_table(Info *table){
  if (table != NULL)
    free(table);
}

#endif
