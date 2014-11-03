#include <stdio.h>
#include <stdlib.h>
typedef int stack_elem_t;
#include "stack.h"// Stack ADT, used to store vertices with degree 0

typedef char *element_t; // define string as element type
// HashTable ADT, used to map strings with numbers
typedef hash_table_record *HashTable;
struct hash_table_record{
  int table_size;
  hash_elem_t *elements;
};

void topological_sort(Graph G){
  Stack S;

  // initialize: push all vertices with in degree 0 into the stack
}
