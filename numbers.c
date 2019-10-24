// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include "numbers.h"
#include <math.h>
#include <ctype.h>
#include <string.h>

//Функция, собирающая число из цифр
double BuildNumber(char const * expression, int begin, int integer, int fract) {
  int i = 1, j = begin;
  double power, number = 0;
  if (expression[integer + j - 1] == '.' || fract > 0) {
    j--;
  }
  while (i <= integer) {
    power = pow(10, integer - i);
    number += (expression[j] - 48) * power;
    j++;
    i++;
  }

  //Прибавляем дробную часть числа
  i = 1;
  j++;
  while (i <= fract) {
    power = pow(10, -i);
    number += (expression[j] - 48) * power;
    j++;
    i++;
  }
  return number;
}
//int SintificRecord (char const * expression)
type_errors_t ReadNumber(char const * expression, stack_t * numbers, int * a, char * buf) {
  int i = *a, k = 0, integer, fract = 0;
  type_errors_t error = 0;
  double number;
  char symbol;
  if (isdigit(*buf)) {
    return TYPE_ERRORS_ENOUGHT_OPERATION;
  }
  for (i; isspace(expression[i]); i++) { ; } //пробелы пропускаем
  for (i, integer = 0; isdigit(expression[i]); i++, integer++) { ; } //смотрим, сколько символов соответствует целой части
  if (expression[i] == '.') {
    i++;
    for (i, fract = 0; isdigit(expression[i]); i++, fract++) { ; } //считаем, сколько чисел соответствует дробной части
    if (expression[i] == '.') {
      return TYRE_ERRORS_REAL_RECORD;
    }
  }
  if (integer > 0 || fract > 0)
  {
    number = BuildNumber(expression, i - integer - fract, integer, fract);
    if (expression[i] == 'e' || expression[i] == 'E') {
      i++;
      symbol = expression[i];
      if (symbol == '-' || symbol == '+') {
        i++;
      }
      //else {
        if (!isdigit(expression[i])) {
          return TYPE_ERRORS_SIENTIFIC_RECORD;
        }
        for (i, k = 0; isdigit(expression[i]); i++, k++) { ; }
        if (k == 0) {
          return TYPE_ERRORS_SIENTIFIC_RECORD;
        }
     // }
        if (symbol == '-') {
          number *= pow(10, -BuildNumber(expression, i - k, k, 0));
        }
        else {
          number *= pow(10, BuildNumber(expression, i - k, k, 0));
        }
      
    }
    *buf = '1';
    error = PutStack(number, numbers);
    *a = i - 1;
    return 0;
  }
  else {
    if (expression[i] == 'e') {
      for (i; isspace(expression[i]); i++) { ; } //пробелы пропускаем
      i++;
      *buf = '1';
      error = PutStack((double)(E), numbers);
    }
    else {
      if (expression[i] == 'p' && expression[++i] == 'i') {
        for (i; isspace(expression[i]); i++) { ; } //пробелы пропускаем
        if (isalnum(expression[i + 1])) {
          return TYPE_ERRORS_UNKNOWN_OPERATION;
        }
        *buf = '1';
        error = PutStack((double)(PI), numbers);
        i++;
      }
      else {
        return TYRE_ERRORS_REAL_RECORD;
      }
    }
  }
  *a = i - 1;
  return error;
}
