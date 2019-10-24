#include "calc.h"

#ifndef STACK_H
#define STACK_H

///Стек операций и чисел
typedef struct {
  double * data;	///<массив значений
  int size;		///<размер стека
  int top;		///<вершина стека
} stack_t;

double GetStack(stack_t * stack);
double WatchStack(stack_t const * stack);
type_errors_t ReSizeStack(stack_t * stack);
type_errors_t PutStack(double object, stack_t * stack);

#endif //STACK_H
