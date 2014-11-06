#define STACK_MIN_SIZE 1
#define EMPTY_STACK -1

typedef struct stack_record *Stack;
struct stack_record{
  int capacity;
  int stack_top;
  stack_elem_t *elements;
};

Stack create_stack(int size);
void dispose_stack(Stack S);
void push(stack_elem_t element, Stack S);
int is_full(Stack S);
int is_empty(Stack S);

Stack create_stack(int size){
  Stack S;

  if (size < STACK_MIN_SIZE){
    printf("Stack size too small\n");
    exit(1);
  }
  S = (Stack)malloc(sizeof(struct stack_record) * size);
  if (S == NULL){
    printf("Out of space while creating a stack\n");
    exit(1);
  }
  S->capacity = size;
  S->elements = (stack_elem_t *)malloc(sizeof(stack_elem_t) * size);
  if (S->elements == NULL){
    printf("Out of space while creating the stack array\n");
    exit(1);
  }
  S->stack_top = EMPTY_STACK;

  return S;
}

void dispose_stack(Stack S){
  if (S != NULL){
    free(S->elements);
    free(S);
  }
}

void push(stack_elem_t element, Stack S){
  if (is_full(S)){
    printf("Push to a full stack\n");
    exit(1);
  }
  S->elements[++S->stack_top] = element;
}

stack_elem_t pop(Stack S){
  stack_elem_t element;

  if (is_empty(S)){
    printf("Pop from an empty stack\n");
    exit(1);
  }
  element = S->elements[S->stack_top--];

  return element;
}

stack_elem_t top(Stack S){
  if (is_empty(S)){
    printf("Trying to get the top of an empty stack\n");
    exit(1);
  }
  return S->elements[S->stack_top];
}

int is_full(Stack S){
  return S->stack_top + 1 == S->capacity;
}

int is_empty(Stack S){
  return S->stack_top == EMPTY_STACK;
}
