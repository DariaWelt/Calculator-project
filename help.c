// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include "help.h"
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
//функция возвращает приоритет операции: 0 - высший; 5 - низший
int Priory(char symbol) {
  priory_operations priority;
  switch (symbol) {
  case '(':
    priority = PRIORY_OPERATIONS_BRACET_FIRST;
    break;
  case ')':
    priority = PRIORY_OPERATIONS_BRACKET_SECOND;
    break;
  case SIN:
  case COS:
  case TAN:
  case CTAN:
  case ARCSIN:
  case ARCCOS:
  case ARCTG:
  case ARCCTG:
  case LN:
  case LOG:
  case FLOOR:
  case CEIL:
  case SQRT:
    priority = PRIORY_OPERATIONS_SINCOS;
    break;
  case '~':
    priority = PRIORY_OPERATIONS_UNARY_MINUS;
    break;
  case '^':
    priority = PRIORY_OPERATIONS_POWER;
    break;
  case '*':
  case '/':
    priority = PRIORY_OPERATIONS_DIV_MULT;
    break;
  case '+':
  case '-':
    priority = PRIORY_OPERATIONS_PLUS_MINUS;
    break;
  default:
    priority = -1;
    break;
  }
  return (int)priority;
}
//функция определяет, что за операция, написанная буквами, перед нами.
char IsOperation(char const * expression, int * i, int* isvar, type_errors_t * error) {
  int k = 0;
  char * operation;
  char oop = 0;
  char symbol = expression[*i];
  operation = (char*)malloc(7 * sizeof(char));//CHECK
  //operation = NULL;
  if (operation == NULL) {
    *error = TYPE_ERRORS_MEMORY;
    return 0;
  }
  for (*i, k = 0; isalnum(expression[*i]) && k < 6; (*i)++, k++) {
    operation[k] = expression[*i];
  }
  (*i)--;
  operation[k] = 0;
  if (!strcmp(operation, "sqrt")){
    oop = SQRT;
  }
  if (!strcmp(operation, "sin")) {
      oop = SIN;
  }
  if (!strcmp(operation, "cos")) {
    oop = COS;
  }
  if (!strcmp(operation, "ctg")) {
    oop = CTAN;
  }
  if (!strcmp(operation, "ceil")) {
    oop = CEIL;
  }
  if (!strcmp(operation, "tg")) {
    oop = TAN;
  }
  if (!strcmp(operation, "ln")) {
    oop = LN;
  }
  if (!strcmp(operation, "log")) {
    oop = LOG;
  }
  if (!strcmp(operation, "arccos")) {
    oop = ARCCOS;
  }
  if (!strcmp(operation, "arcsin")) {
    oop = ARCSIN;
  }
  if (!strcmp(operation, "arctg")) {
    oop = ARCTG;
  }
  if (!strcmp(operation, "floor")) {
    oop = FLOOR;
  }
  if (oop == 0) {
    if (strlen(operation) == 1) {
      *isvar = 1;
      free(operation);
      return symbol;
    }
    else {
      free(operation);
      return 0;
    }
  }
  else {
    free(operation);
    return oop;
  }
}
