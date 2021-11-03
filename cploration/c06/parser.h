#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdint.h>
#define MAX_LINE_LENGTH 200
#define MAX_LABEL_LENGTH MAX_LINE_LENGTH - 2

typedef int16_t hack_addr;
typedef int16_t opcode;

char *strip(char *s);
char *extract_label(const char *line, char* label);

void parse(FILE * file);

int is_Atype(const char *);
int is_label(const char *);
int is_Ctype(const char *);

enum instr_type {
  Invalid = -1,
  A_type, 
  C_type,
};

typedef struct c_instruction {
  opcode a:1;
  opcode comp:6;
  opcode dest:3;
  opcode jump:3;
} c_instruction;

typedef struct a_instruction {
  union instruction_type {
    hack_addr address;
    char *label;
  } instruction_type;
  bool is_addr;
} a_instruction;

typedef struct instruction {
  union a_or_c{
    hack_addr c_instruction;
    hack_addr a_instruction;
  } a_or_c;
  enum instr_type field;
} instruction;
