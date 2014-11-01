typedef struct list_node *List;
struct list_node{
  int element;
  List next;
};

typedef struct hash_table_record *HashTable;
struct hash_table_record{
  int table_size;
  int used_space;
  List *elements;
};

#include "7_2.h"
#include "7_a.h"
List find(int num, HashTable T);

int main(void){
  test();
  return 0;
}

void delete(int num, HashTable T){
  int hash_value;
  List L, prevL;

  hash_value = hash(num, T);
  for (L = T->elements[hash_value], prevL = L;
       L != NULL && L->element != num;
       prevL = L, L = L->next); // find L and its predecessor
  if (L != NULL){ // find
    prevL->next = L->next;
    free(L);
    T->used_space--;
  }
}

List find(int num, HashTable T){
  List L;
  int hash_value = hash(num, T);
  L = T->elements[hash_value];
  while (L != NULL && L->element != num)
    L = L->next;
 
  return L;
}

HashTable rehash(HashTable T0){
  HashTable T;
  List L;

  T = create_hash_table(T0->table_size * 2);
  // reinsert
  for (int i = 0; i < T0->table_size; i++)
    for (L = T0->elements[i]; L->next != NULL; L = L->next)
      insert(L->next->element, T);
  dispose_hash_table(T0);

  return T;
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
  T->elements = (List *)malloc(sizeof(struct list_node) * table_size);
  if (T->elements == NULL){
    printf("Out of space\n");
    exit(1);
  }
  for (int i = 0; i < T->table_size; i++){
    T->elements[i] = (List)malloc(sizeof(struct list_node));
    if (T->elements[i] == NULL){
      printf("Out of space\n");
      exit(1);
    }
    T->elements[i]->element = -1; // set a initial value
    T->elements[i]->next = NULL;
    T->used_space = 0;
  }

  return T;
}

HashTable insert(int num, HashTable T){
  int hash_value;
  List L, new_node;

  if (find(num, T) == NULL){ // not exist
    hash_value = hash(num, T);
    new_node = (List)malloc(sizeof(struct list_node));
    new_node->element = num;
    L = T->elements[hash_value];
    new_node->next = L->next;
    L->next = new_node;
    T->used_space++;
  }
  // when the density is greater then 0.5, rehash
  if (T->used_space > (T->table_size + 1) / 2)
    T = rehash(T);
  return T;
}

int hash(int num, HashTable T){
  return num % T->table_size;
}
