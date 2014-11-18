#ifndef __KRUSKAL_H__
#define __KRUSKAL_H__
#include "graph.h"
#include "disjset.h"
#include "heap.h"

Edge *kruskal(Graph G){
  Set S;
  Heap H;
  int vertex_num;
  int i;
  int edge_num, edge_count;    // record number of edges counted before build a heap
  List L;
  Edge *edges, E;
  int u, v;
  Edge *result;

  // get all edges of G
  vertex_num = G->vertex_num;
  edge_num = G->edge_num;
  S = initialize_set(vertex_num);
  edges = (Edge *)malloc(sizeof(Edge) * edge_num);
  edge_count = 0;
  for (i = 1; i <= vertex_num; i++){
    for (L = G->vertices[i]->next; L != NULL; L = L->next){
      if (L->index > i){    // the graph is undirected, only half of the edge are chosen, choose those whose from ixdex is smaller than to index
        edges[edge_count].length = L->weight;
        edges[edge_count].from = i;
        edges[edge_count].to = L->index;
        edge_count++;
      }
    }
  }

  result = (Edge *)malloc(sizeof(Edge) * vertex_num);
  edge_count = 0;
  H = build_heap(edges, edge_num);
  edge_count = 0;
  while (edge_count < vertex_num - 1){
    E = delete_min(H);
    u = E.from;
    v = E.to;
    if (!is_connected(S, u, v)){
      union_set(S, u, v);
      result[edge_count++] = E;
    }
  }

  free(edges);
  dispose_heap(H);
  dispose_set(S);
  return result;
}

#endif
