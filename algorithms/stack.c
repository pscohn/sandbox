#include <stdio.h>

void print_stack(int *stack) {
  printf("current stack: ");
  for (int i=0; i<8; i++) {
    printf("%i ", stack[i]); 
  }
  printf("\n");
}

void push(int *stack, int *stack_index, int item) {
  stack[(*stack_index)++] = item;
  printf("added %i to stack\n", item); 
  printf("stack index: %i\n", *stack_index); 
  print_stack(stack);
}

int pop(int *stack, int *stack_index) {
  int popped = stack[--(*stack_index)];
  stack[*stack_index] = 0;
  printf("popped %i\n", popped);
  printf("stack index: %i\n", *stack_index); 
  print_stack(stack);
  return popped;  
}

int main() {
  int stack[8];
  int stack_index = 0;

  push(stack, &stack_index, 5);
  push(stack, &stack_index, 3);
  pop(stack, &stack_index);
  push(stack, &stack_index, 4);
  return 0;
}
