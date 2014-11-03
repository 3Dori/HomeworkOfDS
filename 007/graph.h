typedef struct vertex_record{
  int in_degree, out_degree;
  long adjacency;
  // a subtle trick: use a 64 bit vector to represent its adjacency matrix
  // and most operations are involved to bitwise operation
} vertex_t;
// Graph ADT, used to represent a graph
typedef struct graph_record *Graph;
struct graph_record{
  int vertices_num;
  vertex_t *vertices;
};
