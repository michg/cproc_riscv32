#include "io.h"

void printargs(int arg1, ...)
{
  __builtin_va_list ap;
  int i;

  __builtin_va_start(ap, arg1);
  for (i = arg1; i >= 0; i = __builtin_va_arg(ap, int))
    puti(i);
  __builtin_va_end(ap);
  putc('\n');
}


int main()
{
  printargs(5, 2, 14, 84, 97, 15, 32, 48, -1);
  printargs(84, 51, -1);
  return 0;
}
