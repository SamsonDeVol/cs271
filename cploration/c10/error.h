#ifndef __ERROR_H__
#define __ERROR_H__

#include <stdarg.h>

enum exitcode{
  EXIT_INCORRECT_ARGUMENTS = 1,
  EXIT_CANNOT_OPEN_FILE,
  EXIT_TOO_MANY_INSTRUCTIONS,
  EXIT_INVALID_LABEL,
  EXIT_SYMBOL_ALREADY_EXISTS,
  EXIT_INVALID_A_INSTR
};

void exit_program(enum exitcode code, ...);

#endif