#ifndef CALC_H
#define CALC_H
///Ошибки вычисления
typedef enum {
  TYPE_ERRORS_OKAY,				///<нет ошибки
  TYPE_ERRORS_CALCULATION,		///<вычислительная ошибка
  TYPE_ERRORS_OPERANDS,			///<недостаточно операндов
  TYPE_ERRORS_ENOUGHT_OPERATION,///<излишек операндов
  TYPE_ERRORS_UNKNOWN_OPERATION,///<неизвестная операция
  TYPE_ERRORS_MEMORY,			///<ошибка выделения памяти
  TYPE_ERRORS_SIENTIFIC_RECORD, ///<ошибка в научной записи числа
  TYRE_ERRORS_REAL_RECORD,		///<ошибка в вещественной записи числа
  TYPE_ERRORS_VARIABELS,		///<ошибка в переменных
  TYPE_ERRORS_BRACKET			///<излишек/недостаток скобок
} type_errors_t;
void Errors(type_errors_t error);

double Calculate(char * expression, type_errors_t * error);

void Errors(type_errors_t error);
#endif //CALC_H
