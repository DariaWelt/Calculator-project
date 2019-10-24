// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include "calc.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
/*
Функция, проверяющая выражение это или комментарий
Возвращает:	0 - пробелы
            1 - выражение
            2 - комментарий
            3 - ошибочное выражение
*/
int IsExpression(unsigned char const *string) {
  int i = 0;
  int err = 0;
  //int length = strlen(string);
  int length = 0;
  for (length; string[length] != 0; length++) {
    if (string[length] > 126) {
      err = TYPE_ERRORS_UNKNOWN_OPERATION;
    }
  }
  for (i = 0; isspace(string[i]) && i < length; i++) { ; }
  if (i + 1 < length) {
    if ((string[i] == '/') && (string[i + 1] == '/')) {
      return 2;
    }
    else {
      if (err) {
        return 3;
      }
      else {
        return 1;
      }
    }
  }
  else {
    if (err) {
      return 3;
    }
    else {
      if (i < length/* && string[i] != -1*/) {
        return 1;
      }
      else {
        return 0;
      }
    }
  }
}


//Функция, считывающая текст в динамический массив
unsigned char* ReadString(FILE * stream, int* end, type_errors_t * ERR) {
  unsigned char *string, *m;
  type_errors_t error = 0;
  int symbol = 0;
  int i;
  if ((symbol = getc(stream)) == -1) {
    *end = -1;
  }
  string = (unsigned char*)calloc(10, sizeof(unsigned char));//CHECK
  //string = 0;
  if (string == NULL) {
    while (symbol != -1 && symbol != '\n') {
      symbol = getc(stream); 
    }
    if (symbol == -1) {
      *end = -1;
    }
    error = TYPE_ERRORS_MEMORY;
	if (ERR != NULL)
	  *ERR = error;
    return 0;
  }
  string[0] = (unsigned char)symbol;
  for (i = 1; symbol != '\n' && symbol != -1; i++) {
    if ((i % 10) == 9) {
     m = (unsigned char*)realloc(string, (10 + i + 1) * sizeof(unsigned char));//CHECK
      //m = 0;
      if (m != NULL) {
        string = m;
      }
      else {
        //string[i] = 0;
        error = TYPE_ERRORS_MEMORY;
        while (symbol != '\n' && symbol != -1) {
          symbol = (int)getc(stream);
        }
		if (ERR != NULL)
		  *ERR = error;
        return string;
      }
      m = NULL;
    }
    symbol = (int)getc(stream);
    string[i] = (unsigned char)symbol;
  }
  if (symbol == -1) {
    *end = -1;
  }
  string[i - 1] = 0;
  if (ERR != NULL)
    *ERR = error;
  return string;
}



int main(int argc, char* argv[]) {
  unsigned char *str;
  int end = 0;
  double result;
  type_errors_t error = 0;
  FILE * stream = stdin;
  if (argc > 2) {
    printf("ERROR: too many arguments\n");
    //_getch();
    return 0;
  }
  if (argc == 1) {
    stream = stdin;
  }
  if (argc == 2) {
    fopen_s(&stream, argv[1], "r");
  if (stream == NULL){
    printf("ERROR: File is not found\n");
    //_getch();
    return 0;
  }
  }
  do{
    str = ReadString(stream, &end, &error);
    if (error == 0 && IsExpression(str) == 1){
      printf("%s == ", str);
      result = Calculate((char*)str, &error);
      if (error == 0) {
        printf("%g\n", result);
      }
      else {
        Errors(error);
      }
      error = 0;
      free(str);
    }
    else {
      if (error == 0 && IsExpression(str) == 3) {
        error = TYPE_ERRORS_UNKNOWN_OPERATION;
        printf("%s == ", str);
        Errors(error);
        error = 0;
        free(str);
      }
      else {
        if (error == 0 && IsExpression(str) != 1) {
          if (end == -1) {
            free(str);
            fclose(stream);
            //_getch();
            return 0;
          }
          else {
            printf("%s\n", str);
            free(str);
          }
        }
        else {
          free(str);
          if (end == -1) {
            fclose(stream);
           // _getch();
            return 0;
          }
          Errors(error);
          error = 0;
        }
      }
    }
    /*_CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_FILE);
    _CrtSetReportFile(_CRT_WARN, _CRTDBG_FILE_STDOUT);
    _CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_FILE);
    _CrtSetReportFile(_CRT_ERROR, _CRTDBG_FILE_STDOUT);
    _CrtSetReportMode(_CRT_ASSERT, _CRTDBG_MODE_FILE);
    _CrtSetReportFile(_CRT_ASSERT, _CRTDBG_FILE_STDOUT);
    _CrtDumpMemoryLeaks();*/
  } while (!end);
  fclose(stream);
  return 0;
}
