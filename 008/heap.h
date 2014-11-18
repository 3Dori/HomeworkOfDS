#ifndef __HEAP_H__
#define __HEAP_H__
#include <stdio.h>
#include <stdlib.h>
#define HEAP_MIN -1    // sentinel

// The edge ADT
struct edge_record{
  int length;
  int from;
  int to;
};
typedef struct edge_record Edge;
Edge SENTINEL = {HEAP_MIN, 0, 0};    // set a sentinel

typedef struct heap_record *Heap;
struct heap_record{
  int capacity;
  int size;
  Edge *elems;
};

int is_full(Heap H);
int is_empty(Heap H);
Heap create_empty_heap(int size);
Heap build_heap(Edge *seq, int size);
void insert(Heap H, Edge elem);
Edge delete_min(Heap H);
void dispose_heap(Heap H);

void dispose_heap(Heap H){
  if (H != NULL){
    free(H->elems);
    free(H);
  }
}

Heap create_empty_heap(int size){
  Heap H;

  H = (Heap)malloc(sizeof(struct heap_record));
  H->capacity = size;
  H->size = 0;
  H->elems = (Edge *)malloc(sizeof(Edge) * (size + 1));
  H->elems[0] = SENTINEL;

  return H;
}

Heap build_heap(Edge *seq, int size){
  // build a heap using linear time
  Heap H;
  int i, child;
  int percodown_index;
  Edge percodown_elem;

  H = (Heap)malloc(sizeof(struct heap_record));
  H->capacity = size;
  H->size = size;
  H->elems = (Edge *)malloc(sizeof(Edge) * (size + 1));
  H->elems[0] = SENTINEL;

  for (i = 0; i < size; i++)
    H->elems[i + 1] = seq[i];
  for (percodown_index = size / 2; percodown_index > 0; percodown_index--){
    percodown_elem = H->elems[percodown_index];
    for (i = percodown_index; i * 2 <= H->size; i = child){
      child = i * 2;
      if (child + 1 <= H->size && H->elems[child + 1].length < H->elems[child].length)
        child++;
      if (H->elems[child].length < percodown_elem.length)
        H->elems[i] = H->elems[child];
      else
        break;
    }
    H->elems[i] = percodown_elem;
  }
  return H;
}

Edge delete_min(Heap H){
  Edge min, last;
  int child, i;

  if (is_empty(H)){
    printf("Empty heap\n");
    exit(1);
  }
  min = H->elems[1];
  last = H->elems[H->size--];

  for (i = 1; i * 2 <= H->size; i = child){
    child = i * 2;
    if (child + 1 <= H->size && H->elems[child].length > H->elems[child + 1].length)
      child++;
    // percolate down
    if (H->elems[child].length < last.length)
      H->elems[i] = H->elems[child];
    else
      break;
  }
  H->elems[i] = last;

  return min;
}

void insert(Heap H, Edge elem){
  int child;

  if (is_full(H)){
    printf("Full heap\n");
    exit(1);
  }

  for (child = ++H->size; H->elems[child].length > elem.length; child /= 2){
    H->elems[child] = H->elems[child / 2];
  }
  H->elems[child] = elem;
}

int is_full(Heap H){
  return H->size == H->capacity;
}

int is_empty(Heap H){
  return H->size == 0;
}
#endif
