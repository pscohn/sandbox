#include <stdio.h>
#include <assert.h>

#define STACKSIZE 8

typedef struct {
  int stack[STACKSIZE];
  int index;
} Stack;

void print_stack(int *stack) {
  printf("current stack: ");
  for (int i=0; i<STACKSIZE; i++) {
    printf("%i ", stack[i]);
  }
  printf("\n");
}

void push(Stack *stack, int item) {
  if (stack->index == STACKSIZE - 1) {
    fprintf(stderr, "stack is full\n");
    exit(1);
  }
  stack->index++;
  stack->stack[stack->index] = item;
  printf("added %i to stack\n", item);
  printf("stack index: %i\n", stack->index);
  print_stack(&stack->stack[0]);
}

int pop(Stack *stack) {
  if (stack->index == 0) {
    fprintf(stderr, "stack is empty, cannot pop\n");
    exit(1);
  }
  int popped = stack->stack[stack->index];
  stack->stack[stack->index] = 0;
  stack->index--;
  printf("popped %i\n", popped);
  printf("stack index: %i\n", stack->index);
  print_stack(&stack->stack[0]);
  return popped;
}

Stack new_stack() {
  Stack s;
  s.index = -1;
  return s;
}

int main() {
  Stack s = new_stack();
  printf("s.index: %i\n", s.index);

  assert(s.index == -1);
  push(&s, 5);
  assert(s.index == 0);
  assert(s.stack[0] == 5);
  push(&s, 3);
  assert(s.index == 1);
  assert(s.stack[0] == 5);
  assert(s.stack[1] == 3);
  pop(&s);
  assert(s.index == 0);
  assert(s.stack[0] == 5);
  assert(s.stack[1] == 0);
  push(&s, 4);
  push(&s, 4);
  push(&s, 4);
  push(&s, 4);
  push(&s, 4);
  push(&s, 4);
  push(&s, 4);
  push(&s, 4);
  push(&s, 4);
  push(&s, 4);
  push(&s, 4);
  return 0;
}
