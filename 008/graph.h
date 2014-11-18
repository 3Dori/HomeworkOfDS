#ifndef __GRAPH_H__
#define __GRAPH_H__
#include <stdio.h>
#include <stdlib.h>
typedef struct list_record *List;
struct list_record{
  int index;
  int weight;
  List next;
};

typedef struct graph_record *Graph;
struct graph_record{
  int vertex_num;
  int edge_num;
  List *vertices;
};

Graph input_graph(void);
Graph create_graph(int size);
void dispose_list(List L);
void dispose_graph(Graph G);
int is_conncected(Graph G, int a, int b);
void connect_vertices(Graph G, int a, int b, int weight);
void connect_directed(Graph G, int a, int b, int weight);

Graph input_graph(void){
  int vertex_num;
  int connection_num;
  int a, b, weight;
  Graph G;

  scanf("%d%d", &vertex_num, &connection_num);
  G = create_graph(vertex_num);
  for (int i = 0; i < connection_num; i++){
    scanf("%d%d%d", &a, &b, &weight);
    connect_vertices(G, a, b, weight);
  }

  return G;
}

Graph create_graph(int size){
  Graph G;

  G = (Graph)malloc(sizeof(struct graph_record));
  G->vertex_num = size;
  G->edge_num = 0;
  G->vertices = (List *)malloc(sizeof(List) * (size + 1));
  for (int i = 1; i <= size; i++){
    G->vertices[i] = (List)malloc(sizeof(struct list_record));
    G->vertices[i]->next = NULL;
  }
  return G;
}

void dispose_graph(Graph G){
  if (G != NULL){
    for (int i = 0; i <= G->vertex_num; i++)
      dispose_list(G->vertices[i]);
    free(G);
  }
}

void dispose_list(List L){
  // dispose the list strating from L to NULL
  List prev;

  while (L != NULL){
    prev = L;
    L = L->next;
    free(prev);
  }
}

void connect_vertices(Graph G, int a, int b, int weight){
  if (is_conncected(G, a, b))
    return;
  // connect both direction
  connect_directed(G, a, b, weight);
  connect_directed(G, b, a, weight);
  G->edge_num++;
}

void connect_directed(Graph G, int a, int b, int weight){
  List L;

  L = (List)malloc(sizeof(struct list_record));
  L->index = b;
  L->weight = weight;
  L->next = G->vertices[a]->next;
  G->vertices[a]->next = L;
}

int is_conncected(Graph G, int a, int b){
  // return the weight between vertex a and b
  // if a and b are not connected, return 0
  List L;

  if (a > G->vertex_num || b > G->vertex_num){
    printf("Too large index\n");
    exit(1);
  }

  for (L = G->vertices[a]->next; L != NULL; L = L->next)
    if (L->index == b)
      return L->weight;

  return 0;
}
#endif
