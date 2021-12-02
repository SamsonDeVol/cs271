#ifndef __HACK_H__
#define __HACK_H__

#include <inttypes.h>
#include <stddef.h>
#include <string.h>

#define NUM_PREDEFINED_SYMBOLS 23

typedef enum jump_id {
  JMP_INVALID = -1,
  JMP_NULL,
  JMP_JGT,
  JMP_JEQ,
  JMP_JGE,
  JMP_JLT,
  JMP_JNE,
  JMP_JLE,
  JMP_JMP
} jump_id;

typedef enum dest_id {
  DEST_INVALID = -1,
  DEST_NULL,
  DEST_M,
  DEST_D,
  DEST_MD,
  DEST_A,
  DEST_AM,
  DEST_AD,
  DEST_ADM
} dest_id;

typedef enum comp_id {
  COMP_INVALID = -1,
  COMP_NULL,
  COMP_0 = 42,
  COMP_1 = 63,
  COMP_NEGATIVE1 = 58,
  COMP_D = 12,
  COMP_A = 48,
  COMP_NOTD = 13,
  COMP_NOTA = 49,
  COMP_NEGATIVED = 15,
  COMP_NEGATIVEA = 51,
  COMP_DPLUS1 = 31,
  COMP_APLUS1 = 55,
  COMP_DMINUS1 = 14,
  COMP_AMINUS1 = 13,
  COMP_DPLUSA = 2,
  COMP_DMINUSA = 19,
  COMP_AMINUSD = 7,
  COMP_DANDA = 0,
  COMP_DORA = 21,
  COMP_M = 48,
  COMP_NOTM = 49,
  COMP_NEGATIVEM = 51,
  COMP_MPLUS1 = 55,
  COMP_MMINUS1 = 13,
  COMP_DPLUSM = 2,
  COMP_DMINUSM = 19,
  COMP_MMINUSD = 7, 
  COMP_DANDM = 0,
  COMP_DORM = 21
} comp_id;

enum symbol_id {
  SYM_R0 = 0,
  SYM_R1,
  SYM_R2,
  SYM_R3,
  SYM_R4,
  SYM_R5,
  SYM_R6,
  SYM_R7,
  SYM_R8,
  SYM_R9,
  SYM_R10,
  SYM_R11,
  SYM_R12,
  SYM_R13,
  SYM_R14,
  SYM_R15,
  SYM_SCREEN = 16384,
  SYM_KBD = 24576,
  SYM_SP = 0,
  SYM_LCL,
  SYM_ARG,
  SYM_THIS,
  SYM_THAT
} symbol_id;

typedef struct predefined_symbol {
  char name[10];
  int16_t address;
}predefined_symbol;

static const predefined_symbol predefined_symbols[NUM_PREDEFINED_SYMBOLS] = {
  {"R0", SYM_R0},
  {"R1", SYM_R1},
  {"R2", SYM_R2},
  {"R3", SYM_R3},
  {"R4", SYM_R4},
  {"R5", SYM_R5},
  {"R6", SYM_R6},
  {"R7", SYM_R7},
  {"R8", SYM_R8},
  {"R9", SYM_R9},
  {"R10", SYM_R10},
  {"R11", SYM_R11},
  {"R12", SYM_R12},
  {"R13", SYM_R13},
  {"R14", SYM_R14},
  {"R15", SYM_R15},
  {"SCREEN", SYM_SCREEN},
  {"KBD", SYM_KBD},
  {"SP", SYM_SP},
  {"LCL", SYM_LCL},
  {"ARG", SYM_ARG},
  {"THIS", SYM_THIS},
  {"THAT", SYM_THAT},
};

static inline jump_id str_to_jumpid(const char *s){
  jump_id id = JMP_INVALID;
  if (s == NULL){
    id = JMP_NULL;
  }
  else if (strcmp(s, "JGT") == 0){
    id = JMP_JGT;
  }
  else if (strcmp(s, "JEQ") == 0){
    id = JMP_JEQ;
  }
  else if (strcmp(s, "JGE") == 0){
    id = JMP_JGE;
  }
  else if (strcmp(s, "JLT") == 0){
    id = JMP_JLT;
  }
  else if (strcmp(s, "JNE") == 0){
    id = JMP_JNE;
  }
  else if (strcmp(s, "JLE") == 0){
    id = JMP_JLE;
  }
  else if (strcmp(s, "JMP") == 0){
    id = JMP_JMP;
  }
  return id;
}

static inline dest_id str_to_destid(const char *s){
  dest_id id = DEST_INVALID;
  if (strcmp(s, "0") == 0){
    id = DEST_NULL;
  }
  else if (strcmp(s, "M") == 0){
    id = DEST_M;
  }
  else if (strcmp(s, "D") == 0){
    id = DEST_D;
  }
  else if (strcmp(s, "MD") == 0){
    id = DEST_MD;
  }
  else if (strcmp(s, "A") == 0){
    id = DEST_A;
  }
  else if (strcmp(s, "AM") == 0){
    id = DEST_AM;
  }
  else if (strcmp(s, "AD") == 0){
    id = DEST_AD;
  }
  else if (strcmp(s, "ADM") == 0){
    id = DEST_ADM;
  }
  return id;
}

static inline comp_id str_to_compid(const char *s, int *a){
  comp_id id = COMP_INVALID;

  *a = 0;
  if (s == NULL){
    id = COMP_NULL;
  }
  else if (strcmp(s, "0") == 0){
    id = COMP_0;
  }
  else if (strcmp(s, "1") == 0){
    id = COMP_1;
  }
  else if (strcmp(s, "-1") == 0){
    id = COMP_NEGATIVE1;
  }
  else if (strcmp(s, "D") == 0){
    id = COMP_D;
  }
  else if (strcmp(s, "A") == 0){
    id = COMP_A;
  }
  else if (strcmp(s, "!D") == 0){
    id = COMP_NOTD;
  }
  else if (strcmp(s, "!A") == 0){
    id = COMP_NOTA;
  }
  else if (strcmp(s, "-D") == 0){
    id = COMP_NEGATIVED;
  }
  else if (strcmp(s, "-A") == 0){
    id = COMP_NEGATIVEA;
  }
  else if (strcmp(s, "D+1") == 0){
    id = COMP_DPLUS1;
  }
  else if (strcmp(s, "A+1") == 0){
    id = COMP_APLUS1;
  }
  else if (strcmp(s, "D-1") == 0){
    id = COMP_DMINUS1;
  }
  else if (strcmp(s, "A-1") == 0){
    id = COMP_AMINUS1;
  }
  else if (strcmp(s, "D+A") == 0){
    id = COMP_DPLUSA;
  }
  else if (strcmp(s, "D-A") == 0){
    id = COMP_DMINUSA;
  }
  else if (strcmp(s, "A-D") == 0){
    id = COMP_AMINUSD;
  }
  else if (strcmp(s, "D&A") == 0){
    id = COMP_DANDA;
  }
  else if (strcmp(s, "D|A") == 0){
    id = COMP_DORA;
  }
  else if (strcmp(s, "M") == 0){
    id = COMP_M;
    *a = 1;
  }
  else if (strcmp(s, "!M") == 0){
    id = COMP_NOTM;
    *a = 1;
  }
  else if (strcmp(s, "-M") == 0){
    id = COMP_NEGATIVEM;
    *a = 1;
  }
  else if (strcmp(s, "M+1") == 0){
    id = COMP_MPLUS1;
    *a = 1;
  }
  else if (strcmp(s, "M-1") == 0){
    id = COMP_MMINUS1;
    *a = 1;
  }
  else if (strcmp(s, "D+M") == 0){
    id = COMP_DPLUSM;
    *a = 1;
  }
  else if (strcmp(s, "D-M") == 0){
    id = COMP_DMINUSM;
    *a = 1;
  }
  else if (strcmp(s, "M-D") == 0){
    id = COMP_MMINUSD;
    *a = 1;
  }
  else if (strcmp(s, "D&M") == 0){
    id = COMP_DANDM;
    *a = 1;
  }
  else if (strcmp(s, "D|M") == 0){
    id = COMP_DORM;
    *a = 1;
  }
  return id;
}

#endif