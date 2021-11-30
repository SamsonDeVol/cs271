#ifndef __PARSER_H__
#define __PARSER_H__

#include "hack.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdint.h>

#define MAX_LINE_LENGTH 200
#define MAX_LABEL_LENGTH MAX_LINE_LENGTH - 2
#define MAX_HACK_ADDRESS INT16_MAX
#define MAX_INSTRUCTION MAX_HACK_ADDRESS

typedef int16_t hack_addr;
typedef int16_t opcode;

int is_Atype(const char *);
int is_label(const char *);
int is_Ctype(const char *);

enum instr_type {
  Invalid = -1,
  A_type, 
  C_type,
} instr_type;

typedef struct a_instruction {
  union instruction_type {
    hack_addr address;
    char *label;
  } instruction_type;
  bool is_addr;
} a_instruction;

typedef struct c_instruction {
  opcode a:1;
  opcode comp:7;
  opcode dest:4;
  opcode jump:4;
} c_instruction;

typedef struct instruction {
  union a_or_c{
    a_instruction a;
    c_instruction c;
  } a_or_c;
  enum instr_type field;
} instruction;

bool parse_A_instruction(const char *line, a_instruction *instr);
void parse_C_instruction(char *line, c_instruction *instr);
char *strip(char *s);
char *extract_label(const char *line, char* label);
int parse(FILE * file, instruction *instructions);
void add_predefined_symbols();
void assemble(const char * file_name, instruction* instructions, int num_instructions);

#endif