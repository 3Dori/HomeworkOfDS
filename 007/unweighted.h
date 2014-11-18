const int FALSE = 0;
const int TRUE = 1;
const int INF = 10000;    // infinity
const int NOT_A_VERTEX = 0;

typedef struct list_record *List;
struct list_record{    // unweighted graph vertex
  int index;
  List next;
};

typedef struct queue_record *Queue;
struct queue_record{
  int capacity;
  int front;
  int rear;
  int size;
  int *elements;
};

typedef struct info_record Info;
struct info_record{
  int known;
  int dist;
  int path;
} Info;

typedef struct graph_record *Graph;
struct graph_record{
  int vertex_num;
  List *vertices;
};

Queue create_queue(int size){
  Queue Q;

  Q = (Queue)malloc(sizeof(struct queue_record));
  Q->capacity = size;
  Q->elements = malloc(sizeof(int) * size);
  Q->front = -1;
  Q->rear = 0;
  Q->size = 0;

  return Q;
}

void dispose_queue(Queue Q){
  if (Q != NULL){
    free(Q->elements);
    free(Q);
  }
}

int is_full(Queue Q){
  return Q->size == Q->capacity;
}

int is_empty(Queue Q){
  return Q->size == 0;
}

void enqueue(Queue Q, int element){
  if (is_full(Q)){
    printf("Enqueue to a full queue\n");
    exit(1);
  }
  Q->front += 1;
  if (Q->front == Q->capacity)
    Q->front = 0;
  Q->size++;
  Q->elements[Q->front] = element;
}

int dequeue(Queue Q){
  int tmp_rear;

  if (is_empty(Q)){
    printf("Dequeue from an empty queue\n");
    exit(1);
  }
  tmp_rear = Q->rear;
  Q->rear += 1;
  if (Q->rear == Q->capacity)
    Q->rear = 0;
  Q->size--;
  return Q->elements[tmp_rear];
}

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

void connect_to(Graph G, int from, int to){
  List L, from_L;

  L = (List)malloc(sizeof(struct list_record));
  L->index = to;

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

Info *unweighted(Graph G, int from){
  Queue Q;
  List adjacent;
  int vertex;
  Info *table;

  Q = create_queue(G->vertex_num);
  enqueue(Q, from);
  table = create_table(G->vertex_num);
  table[from].dist = 0;

  while (!is_empty(Q)){
    vertex = dequeue(Q);
    table[vertex].known = TRUE;
    for (adjacent = G->vertices[vertex]->next; adjacent != NULL; adjacent = adjacent->next){
      // add all the unvisited adjacent to the queue
      if (table[adjacent->index].dist == INF){
	table[adjacent->index].dist = table[vertex].dist + 1;
	table[adjacent->index].path = vertex;
	enqueue(Q, adjacent->index);
      }
    }
  }

  dispose_queue(Q);
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
