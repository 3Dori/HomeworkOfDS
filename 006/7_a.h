List find(int num, HashTable T);

void dispose_hash_table(HashTable T){
  List L, nextL;

  for (int i = 0; i < T->table_size; i++){
    L = T->elements[i];
    nextL = L->next;
    free(L);
    while (nextL != NULL){
      L = nextL;
      nextL = nextL->next;
      free(L);
    }
  }
  free(T);
}

void print_hash_table(HashTable T){
  int i;
  List L;

  for (i = 0; i < T->table_size; i++){
    printf("key %d: ", i);
    for (L = T->elements[i]; L->next != NULL; L = L->next)
      printf("%d ", L->next->element);
    putchar('\n');
  }
}
