// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include "stack.h"
#include <stdlib.h>

//Стек и функции для работы со стеком
type_errors_t ReSizeStack(stack_t *stack) {
  stack_t m;
  m.data = (double*)realloc(stack->data, (stack->size + 1) * sizeof(double));//CHAC
  //m.data = 0;
  if (m.data == NULL) {
    return TYPE_ERRORS_MEMORY;
  }
  else {
    stack->data = m.data;
    stack->size += 1;
    m.data = NULL;
  }
  return TYPE_ERRORS_OKAY;
}
type_errors_t PutStack(double object, stack_t *stack) {
  type_errors_t error = TYPE_ERRORS_OKAY;
  if (stack->top == stack->size) {
    error = ReSizeStack(stack);
  }
  if (error == TYPE_ERRORS_OKAY) {
    stack->data[stack->top] = object;
    stack->top++;
  }
  return error;
}
double GetStack(stack_t *stack) {
  double object;
  object = stack->data[stack->top - 1];
  stack->top--;
  return object;
}
double WatchStack(stack_t const *stack) {
  return stack->data[stack->top - 1];
}
