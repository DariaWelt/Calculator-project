// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include "stack.h"
#include "numbers.h"
#include "сalc.h"
#include "help.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

// to avoid warnings issued by pvs
char FromDoubleToChar(double arg) {
  int number = 0;
  while (number < floor(arg)) {
    ++number;
  }
  return (char)number;
}
void Errors(type_errors_t error) {
  char nameError[TYPE_ERRORS_BRACKET + 1][57] = { "okay",
              "calculation error (e.g. division by 0)",
              "not enough operands",
              "not enough operations (maybe numbers without operations)",
              "unknown operation",
              "not enough memory",
              "scientific record",
              "real record",
              "wrong with variables",
              "Wrong using brackets" };
  if ((int)error > 0) {
    printf("ERROR: %s\n", nameError[(int)error]);
  }
}

//Логарифм от b по основанию a
double LogA(double a, double b) {
  return log(b) / log(a);
}
/*
Функция Compare сравнивает два оператора, то есть:
Возвращает:
      -1 - символ не является операцией
       1 - операцию необходимо записать в стек
       0 - операция имеет приоритет ниже и мы должны вынуть предыдущее значение из стека
*/
int Compare(char symbolString, char symbolStack, stack_t* operations) {
  int priorString = Priory(symbolString);
  int priorStack = Priory(symbolStack);
  if (operations->top == 0) {			//Если в стеке ниичего не лежит, записываем в стек
    return 1;
  }
  if ((priorStack == -1) || (priorString == -1)) {
    //если неизвестный символ - возвращаем ошибку
    return -1;
  }
  if (priorStack == PRIORY_OPERATIONS_UNARY_MINUS && priorString == PRIORY_OPERATIONS_SINCOS) {
    priorStack = PRIORY_OPERATIONS_SINCOS;
  }
  if ((priorString - priorStack < 0) || (priorStack == 0 && (priorString - priorStack != PRIORY_OPERATIONS_BRACKET_SECOND))) {
    return 1;			//если приоритет выше и это не две скобки - записываем
  }
  else {
    if (priorString - priorStack == PRIORY_OPERATIONS_BRACKET_SECOND) {
      return 2;
    }
    else {
      if ((priorString == PRIORY_OPERATIONS_POWER && priorStack > 1) || priorString == PRIORY_OPERATIONS_SINCOS) { //для степени
        return 1;
      }
      else {
        return 0;
      }
    }
  }

}
// Функция считает 1 унарную операцию
type_errors_t CountingUnary(stack_t *operations, stack_t *numbers) {
  double tempResult = 0;
  char operation = FromDoubleToChar(GetStack(operations));
  double a = 0;
  type_errors_t error = 0;
  //определение операндов
  if (numbers->top > 0) {
    a = GetStack(numbers);
  }
  else {
    //printf("ERROR: not enough operands unary\n");
    return TYPE_ERRORS_OPERANDS;
  }
  switch (operation) {
  case SIN:
    if (floor(a / PI) - (a / (PI)) == 0){
      tempResult = 0;
    }
    else {
      tempResult = sin(a);
    }
    break;
  case COS:
    if (floor(a / PI) - (a / (PI)) == 0) {
      tempResult = cos(a);
    }
    else {
      if (floor(a / (PI / 2)) - (a / (PI / 2)) == 0) {
        tempResult = 0;
      }
      else {
        tempResult = cos(a);
      }
    }
    break;
  case TAN:
    if (floor(a / PI) - (a / (PI)) == 0) {
      tempResult = 0;
    }
    else {
      if (floor(a / (PI / 2)) - (a / (PI / 2)) == 0) {
        return TYPE_ERRORS_CALCULATION;
      }
      else {
        tempResult = tan(a);
      }
    }
    break;
  case CTAN:
    if (floor(a / PI) - (a / PI) == 0) {
      return TYPE_ERRORS_CALCULATION;
    }
    else {
      if (floor(a / (PI / 2)) - (a / (PI / 2)) == 0) {
        tempResult = 0;
      }
      else {
        tempResult = 1 / tan(a);
      }
    }
    break;
  case ARCSIN:
    if (a < -1 || a > 1) {
      return TYPE_ERRORS_CALCULATION;
    }
    tempResult = asin(a);
    break;
  case ARCCOS:
    if (a < -1 || a > 1) {
      return TYPE_ERRORS_CALCULATION;
    }
    tempResult = acos(a);
    break;
  case ARCTG:
    tempResult = atan(a);
    break;
  case ARCCTG:
    tempResult = atan(1 / a);
    break;
  case LN:
    if (a <= 0) {
      return TYPE_ERRORS_CALCULATION;
    }
    tempResult = log(a);
    break;
  case CEIL:
    tempResult = ceil(a);
    break;
  case FLOOR:
    tempResult = floor(a);
    break;
  case SQRT:
    if (a < 0) {
      return TYPE_ERRORS_CALCULATION;
    }
    tempResult = sqrt(a);
    break;
  case '~':
    tempResult = (0 - a);
    break;
  default:
    return TYPE_ERRORS_UNKNOWN_OPERATION;
    break;
  }
  error = PutStack(tempResult, numbers);
  return error;
}
// Функция считает 1 бинарную операцию
type_errors_t CountingBinary(stack_t *operations, stack_t *numbers) {
  double tempResult = 0;
  char operation = FromDoubleToChar(GetStack(operations));
  //определение операндов
  double a = 0, b = 0;
  type_errors_t error = 0;
  if (operation == '(') {// скобка - не операция - пропускаем
    return 0;
  }
  if (numbers->top > 1) {
    b = GetStack(numbers);
    a = GetStack(numbers);
  }
  else {
    return TYPE_ERRORS_OPERANDS;
  }
  // определение операции и вычисление
  switch (operation) {
  case '^':
    tempResult = pow(a, b);
    if (a == 0 && b < 0) {
      return TYPE_ERRORS_CALCULATION;
    }
    if (tempResult != tempResult) {
      return TYPE_ERRORS_CALCULATION;
    }
    break;
  case '*':
    tempResult = a * b;
    break;
  case '/':
    if (b == 0) {
      return TYPE_ERRORS_CALCULATION;
    }
    tempResult = (double)a / b;
    break;
  case '+':
    tempResult = a + b;
    break;
  case '-':
    tempResult = a - b;
    break;
  case 'o':
    if (a == 1 || a < 0 || b <= 0) {
      return TYPE_ERRORS_CALCULATION;
    }
    tempResult = LogA(a, b);
    break;
  default:
    return TYPE_ERRORS_UNKNOWN_OPERATION;
    break;
  }
  error = PutStack(tempResult, numbers);
  return error;
}
// Функция определяет, бинарная это операция или унарная и перенаправляет данные в соответствующие функции.
int Counting(stack_t *operations, stack_t *numbers) {
  char operation = FromDoubleToChar(WatchStack(operations));
  int error = 0;
  if (operation < 'A' || operation == 'o' || operation == '^') {
    error = CountingBinary(operations, numbers);
  }
  else {
    error = CountingUnary(operations, numbers);
  }
  return error;
}
//Функция, работающая со стеком: положить, вычислить до нужного момента, записать результат промежуточных вычислений
type_errors_t WorkWithStack(char symbol, stack_t* operations, stack_t *numbers, char * temp)
{
  type_errors_t error = 0;
  if (operations->top < 0) {
    return TYPE_ERRORS_BRACKET;
  }
  if (operations->top == 0) {
    operations->data[0] = (double)symbol;
    operations->top = 1;
    *temp = '-';
    return TYPE_ERRORS_OKAY;
  }
  if (symbol == 0) {
    symbol = FromDoubleToChar(WatchStack(operations));
    if (symbol == '(' || symbol == ')') {
      return TYPE_ERRORS_BRACKET;
    }
    while (operations->top > 0 && error == TYPE_ERRORS_OKAY) {
      error = Counting(operations, numbers);
      if (error != TYPE_ERRORS_OKAY) {
        break;
      }
      /////
      symbol = FromDoubleToChar(WatchStack(operations));
      if (symbol == '(' || symbol == ')') {
        return TYPE_ERRORS_BRACKET;
      }
    }
  }
  else  {
    switch (Compare(symbol, FromDoubleToChar(WatchStack(operations)), operations)) {
    case (-1):
      return TYPE_ERRORS_UNKNOWN_OPERATION;
      break;
    case (1):
      error = PutStack(symbol, operations);
      *temp = '-';
      break;
    default:
      while (!Compare(symbol, FromDoubleToChar(WatchStack(operations)), operations) && error == TYPE_ERRORS_OKAY) {
        error = Counting(operations, numbers);
      }
      *temp = '1';
      if (error != 0) {
        return error;
      }
      if (symbol == ')') {
        operations->top--;
        if (FromDoubleToChar(WatchStack(operations)) > 96 && FromDoubleToChar(WatchStack(operations)) != 'o') {
          error = Counting(operations, numbers);
        }
      }
      else {
        error = PutStack(symbol, operations);
        *temp = '-';
      }
      break;
    }
  }
  return error;
}
int UnaryMinus(char * expression, int * i) {
  char symbol;
  int sign = -1, k;
  while (expression[*i] == '-') {
    k = *i;
    symbol = expression[(*i)++];
    for (; isspace(expression[*i]); (*i)++) { ; } //пробелы пропускаем
    if (expression[*i] == '-') {
      sign *= -1;
    }
    else {
      *i = k;
      return sign;
    }
  }
  return sign;
}
type_errors_t ItIsVar(variabel_t* s5, char var, int* dat) {
  int i = 0;
  type_errors_t flag = TYPE_ERRORS_VARIABELS;
  for (i; i < s5->top; i++) {
    if (var == s5->variables[i]) {
      *dat = i;
      flag = TYPE_ERRORS_OKAY;
    }
  }
  return flag;
}
type_errors_t ReadOperation(char const * expression, stack_t* numbers, stack_t * operations, int * a, char * temp, variabel_t* s5, int* countingS5Data, int* countingS5Var) {
  int i = *a, k = 0, isvar = 0, numberOfArray = 0;
  char symbol;
  type_errors_t error = 0;
  int sign;
  for (i; isspace(expression[i]); i++) { ; } //пробелы пропускаем
  //если операция - текстовая
  if (isalpha(expression[i])) {
    if (isdigit(*temp)) {
      return TYPE_ERRORS_ENOUGHT_OPERATION;
    }
    symbol = IsOperation(expression, &i, &isvar, &error);
    if (error != TYPE_ERRORS_OKAY) {
      return error;
    }
    // если встретили переменную:
    if (isvar == 1) {
      for (++i; isspace(expression[i]); i++) { ; } //пробелы пропускаем
      if (expression[i] == '=') {
          s5->variables[s5->top] = symbol;
          (*countingS5Var)++;
          *temp = '-';
      }
      else {
        error = ItIsVar( s5, symbol, &numberOfArray);
        if (error == TYPE_ERRORS_OKAY) {
          error = PutStack(s5->data[numberOfArray], numbers);
          *temp = '1';
          i--;
        }
      }
      *a = i;
      return error;
    }
    *temp = '-';
    error = WorkWithStack(symbol, operations, numbers, temp);
  }
  else {
    //проверяем унарный минус
    if (expression[i] == '-') {
      sign = UnaryMinus((char*)expression, &i);
      if (!isdigit(*temp)) {
        if (sign == -1) {
          error = PutStack('~', operations);
          *temp = '-';
        }
      }
      else {
        if (sign == 1) {
          error = WorkWithStack('+', operations, numbers, temp);
        }
        else {
          error = WorkWithStack(expression[i], operations, numbers, temp);
        }
      }
    }
    //остальные "обычные" операции
    else {
      if (expression[i] == '(') {
        for (k = i + 1; isspace(expression[k]); k++) { ; }  //пробелы пропускаем
        if (expression[k] == ')') {
          return TYPE_ERRORS_BRACKET;
        }
      }
      if (!isdigit(*temp) && expression[i] != '(') {
        error = TYPE_ERRORS_OPERANDS;
      }
      //обработка переменных
      if (expression[i] == ';') {
        error = WorkWithStack(0, operations, numbers, temp);
        s5->data[s5->top] = numbers->data[0];
        (*countingS5Data)++;
        numbers->top = 0;
        operations->top = 0;
        *temp = '-';
        if (error == TYPE_ERRORS_OKAY) {
          error = ReSizeVariabel(s5);
        }
        return error;
      }
      //обработка логарифма
      if (expression[i] == ',') {
        error = WorkWithStack(')', operations, numbers, temp);
        if (WatchStack(operations) != LOG) {
          return TYPE_ERRORS_UNKNOWN_OPERATION;
        }
        error = WorkWithStack('(', operations, numbers, temp);
        return error;
      }
      if (error == TYPE_ERRORS_OKAY) {
        if (expression[i] == ')' ){
          for (k = i + 1; isspace(expression[k]); k++){;}
          if (expression[k] == '(') {
            return TYPE_ERRORS_BRACKET;
          }
        }
        error = WorkWithStack(expression[i], operations, numbers, temp);
      }
    }
  }
  *a = i;
  return error;
}
int ReSizeVariabel(variabel_t * arr) {
  char * m;
  double * n;
  m = realloc(arr->variables, (arr->top + 2) * sizeof(char));//CHECK
  //m = NULL;
  if (m == NULL) {
    return TYPE_ERRORS_MEMORY;
  }
  n = realloc(arr->data, (arr->top + 2) * sizeof(double)); //CHECK
  //n = NULL;
  if (n == NULL) {
    if (arr->variables == m) {
      arr->variables = NULL;
    }
     free(m);
     m = NULL;
    return TYPE_ERRORS_MEMORY;
  }
  arr->data = n;
  arr->variables = m;
  (arr->top)++;
  return TYPE_ERRORS_OKAY;
}
double Calculate(char * expression, type_errors_t* ERR) {
  int i, length = strlen(expression);
  type_errors_t error = 0;
  double result;
  char temp = 'a'; //переменная, в которой мы храним предыдущее значение, записанное в стеки (это либо число, либо операция). temp нужен для обработки унарного минуса.
  stack_t operations = { 0, 10, 0 };
  stack_t numbers = { 0, 10, 0 };
  variabel_t s5 = { 0, 0, 0 };
  int countingS5Data = 0;
  int countingS5Var = 0;
  //Выделение памяти под массивы в структурах
  s5.data = (double*)malloc(1 * sizeof(double));//CHECK
  //s5.data = NULL;
  s5.variables = (char*)malloc(1 * sizeof(char));//CHECK
  //s5.variables = NULL;
  numbers.data = (double*)malloc(10 * sizeof(double));//CHECK
  //numbers.data = 0;
  operations.data = (double*)malloc(10 * sizeof(double));//CHECK
  //operations.data = 0;
  if (operations.data == NULL || numbers.data == NULL || s5.data == NULL || s5.variables == NULL) {
    free(s5.data);
    free(s5.variables);
    free(numbers.data);
    free(operations.data);
    error = TYPE_ERRORS_MEMORY;
	if (ERR != NULL) {
	  *ERR = error;
	}
    return 0;
  }
  // бежим по строке и сразу работаем с ней:  считываем операцио или число в соответствующих функциях
  for (i = 0; (i <= length) && (error == TYPE_ERRORS_OKAY); i++) {
    for (i; isspace(expression[i]); i++) { ; } //пробелы пропускаем
    if ((isdigit(expression[i]) || (expression[i] == 'p' && expression[i + 1] == 'i') || expression[i] == 'e' || expression[i] == '.') && i < length) {
      error = ReadNumber(expression, &numbers, &i, &temp);
    }
    else { 
      error = ReadOperation(expression, &numbers, &operations, &i, &temp, &s5, &countingS5Data, &countingS5Var); 
    }
  }
  if (countingS5Data != countingS5Var && error == 0) {
    error = TYPE_ERRORS_VARIABELS;
  }
  free(operations.data);
  if (numbers.top != 1 && error == 0) {
    error = TYPE_ERRORS_OPERANDS;
  }
  result = numbers.data[0];
  free(numbers.data);

  free(s5.variables);
  free(s5.data);

  if (ERR != NULL) {
	  *ERR = error;
	}
  return result;
}
