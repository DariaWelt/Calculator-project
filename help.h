#include "stack.h"
#include "calc.h"

#ifndef HELP_H
#define HELP_H

///Приоритеты операций
typedef enum {
  PRIORY_OPERATIONS_BRACET_FIRST,	///<открывающая скобка
  PRIORY_OPERATIONS_SINCOS,			///<унарные операции за исключением минуса
  PRIORY_OPERATIONS_UNARY_MINUS,	///<унарный минус
  PRIORY_OPERATIONS_POWER,			///<возведение в степень
  PRIORY_OPERATIONS_DIV_MULT,		///<умножение и деление
  PRIORY_OPERATIONS_PLUS_MINUS,		///<сложение и вычитание
  PRIORY_OPERATIONS_BRACKET_SECOND	///<закрывающая скобка
} priory_operations;

///Два связанных массива переменная-значение
typedef struct {
  double * data;		///<значение переменной
  char * variables;		///<обозначение переменой
  int top;				///<количество переменных
} variabel_t; 

///functions
#define COS 'c'			///<косинус
#define SIN 's'			///<синус
#define LN 'l'			///<натуральный логарифм
#define TAN 't'			///<тангенс
#define CTAN 'g'		///<котангенс
#define ARCCOS 'C'		///<арккосинус
#define ARCSIN 'S'		///<акрсинус
#define ARCTG 'T'		///<арктангенс
#define ARCCTG 'G'		///<арккотангенс
#define LOG 'o'			///<логарифм по произвольному основанию
#define FLOOR 'f'		///<округление вниз
#define CEIL 'i'		///<округление вверх
#define SQRT 'q'		///<корень квадратный

int ReSizeVariabel(variabel_t * arr);
int ItIsVar(variabel_t * s5, char var, int * dat);
type_errors_t ReadOperation(char const * expression, stack_t * numbers, stack_t * operations, int * a, char * temp, variabel_t * s5, int* countingS5Data, int * countingS5Var);
int Priory(char symbol);
char IsOperation(char const * expression, int * i, int * isvar, type_errors_t * error);

#endif //HELP_H
