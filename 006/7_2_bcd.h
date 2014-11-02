#ifndef __7_2_BCD_H__
#define __7_2_BCD_H__
typedef enum status_record {legitimate, empty, deleted} Status;
/*
  legitimate: used
  empty: can be used
*/

typedef struct hash_entry Cell;
struct hash_entry{
  int element;
  Status status;
};

typedef struct hash_table_record *HashTable;
struct hash_table_record{
  int table_size;
  int used_space; // record how many entries has been used
  Cell *elements;
};

#include "7_2.h"
HashTable rehash(HashTable T0);
int find(int num, HashTable T);

HashTable rehash(HashTable T0){
  HashTable T;

  T = create_hash_table(T0->table_size * 2);
  for (int i = 0; i < T0->table_size; i++)
    if (T0->elements[i].status == legitimate) // not empty or deleted
      insert(T0->elements[i].element, T);
  dispose_hash_table(T0);

  return T;
}

void delete(int num, HashTable T){
  int pos;

  pos = find(num, T);
  if (pos == -1 || T->elements[pos].status == empty) // not find
    return;
  T->elements[pos].status = deleted;
}

void dispose_hash_table(HashTable T){
  free(T->elements);
  free(T);
}

HashTable insert(int num, HashTable T){
  int pos;

  pos = find(num, T);
  if (pos == -1)
    return T;
  if (T->elements[pos].status != legitimate){
    T->elements[pos].element = num;
    T->elements[pos].status = legitimate;
    T->used_space++;
  }
  if (T->used_space > (T->table_size + 1) / 2)
    T = rehash(T);

  return T;
}

void print_hash_table(HashTable T){
  int i;

  for (i = 0; i < T->table_size; i++){
    printf("Key %d: ", i);
    if (T->elements[i].status == legitimate)
      printf("%d", T->elements[i].element);
    putchar('\n');
  }
}

HashTable create_hash_table(int table_size){
  HashTable T;

  if (table_size < MIN_SIZE){
    printf("Size too small\n");
    exit(1);
  }
  T = (HashTable)malloc(sizeof(struct hash_table_record));
  if (T == NULL){
    printf("Out of space\n");
    exit(1);
  }
  T->table_size = next_prime(table_size);
  T->elements = (Cell *)malloc(sizeof(Cell) * T->table_size);
  if (T->elements == NULL){
    printf("Out of space\n");
    exit(1);
  }
  for (int i = 0; i < T->table_size; i++){
    T->elements[i].status = empty;
    T->used_space = 0;
    T->elements[i].element = -1;
  }

  return T;
}

int hash(int num, HashTable T){
  return num % T->table_size;
}
#endif
