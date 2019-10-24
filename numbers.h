#include "stack.h"

#ifndef NUMB_H
#define NUMB_H
///const
#define PI 3.141592653589793238462643383279 ///<константа PI
#define E 2.7182818284590452353602874713527 ///<константа E

double BuildNumber(char const * expression, int begin, int integer, int fract);
int ReadNumber(char const * expression, stack_t * numbers, int * a, char * buf);

#endif //NUMB_H
