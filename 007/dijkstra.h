const int FALSE = 0;
const int TRUE = 1;
const int INF = 10000;    // infinity
const int NOT_A_VERTEX = 0;
typedef struct list_record *List;
struct list_record{
  int index;
  int weight;
  List next;
};

typedef struct info_recort Info;
struct info_record{
  int known;
  int dist;
  int path;
};

typedef struct graph_record *Graph;
struct graph_record{
  int vertex_num;
  List *vertices;
};

Graph create_graph(int size){
  Graph G;

  G = (Graph)malloc(sizeof(struct graph_record));
  G->vertex_num = size;
  G->vertices = (List *)malloc(sizeof(struct list_record) * (size + 1));
  for (int i = 1; i <= size; i++){
    G->vertices[i] = (List)malloc(sizeof(struct list_record));
    G->vertices[i]->next = NULL;
  }

  return G;
}

void dispose_graph(Graph G){
  List L, prev;

  if (G != NULL){
    // dispose lists
    for (int i = 1; i <= G->vertex_num; i++)
      for (L = G->vertices[i]; L != NULL;){
	prev = L;
	L = L->next;
	free(prev);
      }
    free(G->vertices);
    free(G);
  }
}

void connect_to(Graph G, int from, int to, int weight){
  List L, from_L;

  L = (List)malloc(sizeof(struct list_record));
  L->index = to;
  L->weight = weight;

  from_L = G->vertices[from];
  L->next = from_L->next;
  from_L->next = L;
}

Info *create_table(int size){
  Info *table;

  table = (Info *)malloc(sizeof(Info) * (size + 1));
  for (int i = 1; i <= size; i++){
    table[i].known = FALSE;
    table[i].dist = INF;
    table[i].path = NOT_A_VERTEX;
  }

  return table;
}

void dispose_table(Info *table){
  if (table != NULL)
    free(table);
}

Info *dijkstra(Graph G, int from){
  List adjacent;
  Info *table;
  int has_unknown;
  int smallest_unknown, smallest_dist;

  table = create_table(G->vertex_num);

  table[from].dist = 0;
  for (;;){
    smallest_dist = INF;
    has_unknown = FALSE;
    for (int i = 1; i <= G->vertex_num; i++){
      if (!table[i].known){
	has_unknown = TRUE;
	if (table[i].dist <= smallest_dist){
	  smallest_unknown = i;    // get the smallest unknown distance vertex
	  smallest_dist = table[i].dist;
	}
      }
    }
    if (!has_unknown)
      break;

    table[smallest_unknown].known = TRUE;
    for (adjacent = G->vertices[smallest_unknown]->next; adjacent != NULL; adjacent = adjacent->next){
      if (!table[adjacent->index].known)
	if (table[smallest_unknown].dist + adjacent->weight < table[adjacent->index].dist){
	  table[adjacent->index].dist = table[smallest_unknown].dist + adjacent->weight;
	  table[adjacent->index].path = smallest_unknown;
	}
    }
  }
  return table;
}

void print_path(Info *table, int to){
  // recursively print the path to a vertex
  if (table[to].path == NOT_A_VERTEX){
    printf("%d", to);
    return;
  }
  print_path(table, table[to].path);
  printf(" -> %d", to);
}
