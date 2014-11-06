typedef int stack_elem_t;
#include "stack.h" // Stack ADT, used to store vertices with degree 0
// header file for graph routine
// including creating, disposing, connecting, deleting connection

// Vertex list
typedef struct vertex_list *Vertex;
struct vertex_list{
  int this;
  Vertex next;
};

// Graph ADT, used to represent a graph
typedef struct graph_record *Graph;
struct graph_record{
  int vertices_num;
  Vertex *vertices;
};

Graph create_graph(int vertices_num);
void dispose_graph(Graph G);
void connect_vertices(Graph G, int v1, int v2);
int vertices_are_connected(Graph G, int v1, int v2);
void delete_connection(Graph G, int v1, int v2);
void topological_sort(Graph G);

Graph create_graph(int vertices_num){
  Graph G;
  Vertex V;

  G = (Graph)malloc(sizeof(struct graph_record));
  if (G == NULL){
    printf("Out of space while creating the graph\n");
    exit(1);
  }
  G->vertices_num = vertices_num;
  G->vertices = (Vertex *)malloc(sizeof(struct vertex_list) * (vertices_num + 1));
  if (G->vertices == NULL){
    printf("Out of space while creating the graph vertices\n");
    exit(1);
  }
  for (int i = 0; i <= vertices_num; i++){
    V = (Vertex)malloc(sizeof(struct vertex_list));
    V->next = NULL;
    G->vertices[i] = V;
  }
  return G;
}

void dispose_graph(Graph G){
  Vertex V, prev;

  if (G != NULL){
    // free adjacent vertices
    for (int i = 0; i <= G->vertices_num; i++){
      V = G->vertices[i]->next;
      prev = V;
      while (V != NULL){
	V = V->next;
	free(prev);
	prev = V;
      }
    }
    // free vertices
    free(G->vertices);
    free(G);
  }
}

void connect_vertices(Graph G, int v1, int v2){
  // v1 -> v2
  Vertex V;

  if (vertices_are_connected(G, v1, v2))
    return;
  else{
    V = (Vertex)malloc(sizeof(struct vertex_list));
    V->this = v2;
    V->next = G->vertices[v1]->next;
    G->vertices[v1]->next = V;
  }
}

int vertices_are_connected(Graph G, int v1, int v2){
  Vertex V;

  if ((v1 > G->vertices_num || v2 > G->vertices_num) && v1 && v2){
    printf("Vertex index too large or too small\n");
    exit(1);
  }
  V = G->vertices[v1]->next;
  while (V != NULL){
    if (V->this == v2)
      return 1;
    else
      V = V->next;
  }

  return 0;
}

void delete_connection(Graph G, int v1, int v2){
  Vertex V, prev;

  if ((v1 > G->vertices_num || v2 > G->vertices_num) && v1 && v2){
    printf("Vertex index too large or too small\n");
    exit(1);
  }
  V = G->vertices[v1]->next;
  prev = G->vertices[v1];
  while (V != NULL){
    if (V->this == v2){ // found
      prev->next = V->next;
      free(V);
      break;
    }
    else{
      prev = V;
      V = V->next;
    }
  }
}

void topological_sort(Graph G){
  Stack S;
  Vertex V;
  int *in_degree;
  int current_v, target_v;
  int *result;
  int counter;

  // initialize: push all vertices with in degree 0 into the stack
  S = create_stack(G->vertices_num);
  in_degree = (int *)malloc(sizeof(int) * (G->vertices_num + 1));
  if (in_degree == NULL){
    printf("Out of space while creating the in-degree list\n");
    exit(1);
  }
  for (int i = 1; i <= G->vertices_num; i++)
    in_degree[i] = 0; // set initial value of 0
  for (int i = 1; i <= G->vertices_num; i++){
    V = G->vertices[i];
    while (V != NULL){
      // when there's a vertex connecting to another, increase the latter's in-degree
      in_degree[V->this]++;
      V = V->next;
    }
  }
  for (int i = 1; i <= G->vertices_num; i++)
    if (in_degree[i] == 0) // pick all 0 in-degree vertices and push to stack
      push(i, S);

  result = (int *)malloc(sizeof(int) * G->vertices_num);
  if (result == NULL){
    printf("Out of space while creating result\n");
    exit(1);
  }
  counter = 0;
  while (!is_empty(S)){
    current_v = pop(S); // pop a vertex
    result[counter++] = current_v;
    // get all its adjacent vertices
    V = G->vertices[current_v]->next;
    while (V != NULL){
      if (--in_degree[V->this] == 0){
	push(V->this, S);
	target_v = V->this;
	V = V->next;
	delete_connection(G, current_v, target_v);
      }
      else
	V = V->next;
    }
  }

  if (counter != G->vertices_num)
    printf("Graph has a cycle! ");
  else
    for (int i = 0; i < G->vertices_num; i++)
      printf("%d ", result[i]);
  putchar('\b');

  free(in_degree);
  free(result);
  dispose_stack(S);
}
