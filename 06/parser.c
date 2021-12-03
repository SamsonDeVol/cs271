#include "parser.h"
#include "error.h"
#include "symtable.h"
#include <string.h>

void add_predefined_symbols(){
  for(int i=0; i<NUM_PREDEFINED_SYMBOLS; i++){
    predefined_symbol symbol = predefined_symbols[i];
    symtable_insert(symbol.name, symbol.address);
  }
}

bool parse_A_instruction(const char *line, a_instruction *instr){
  char *s = malloc(strlen(line));
  strcpy(s, line+1);
  char *s_end = NULL;
  long result = strtol(s, &s_end, 10);
  if(s == s_end){
    instr->instruction_type.label = malloc(strlen(line));
    strcpy(instr->instruction_type.label, s);
    instr->is_addr = false;
  }
  else if(*s_end != 0){
    return false;
  }
  else{
    instr->instruction_type.address = result;
    instr->is_addr = true;
  }
  return true;

}

void parse_C_instruction(char *line, c_instruction *instr){
  char *token = NULL;
  char *temp = NULL;
  int a_value =  0;

  token = strtok(line, ";");
  temp = token;
  token = strtok(NULL, ";");
  instr->jump = str_to_jumpid(token);

  token = strtok(temp, "=");
  instr->dest = str_to_destid(token);

  token = strtok(NULL, "=");
  instr->comp = str_to_compid(token, &a_value);
  instr->a = a_value;
}

void assemble(const char * file_name, instruction* instructions, int num_instructions){  
  opcode op;
  int new_address = 16;
  char *hack_file = strncat(file_name, ".hack", 5);
  FILE *hack = fopen(hack_file, "w");
  for (int i=0; i < num_instructions; i++){
   
   if(instructions[i].field == 0 ){
      if(instructions[i].a_or_c.a.is_addr == false){
        if(symtable_find(instructions[i].a_or_c.a.instruction_type.label)){
          op = instructions[i].a_or_c.a.instruction_type.address;
          printf("label: %s\n", symtable_find(instructions[i].a_or_c.a.instruction_type.label)->name);
        }
        else {
          symtable_insert(instructions[i].a_or_c.a.instruction_type.label, new_address++);
          op = instructions[i].a_or_c.a.instruction_type.address;
          printf("new label: %s\n", symtable_find(instructions[i].a_or_c.a.instruction_type.label)->name);
        }
        free(instructions[i].a_or_c.a.instruction_type.label);
      }
      else {
        op = instructions[i].a_or_c.a.instruction_type.address;
        printf("instruction is a-address\n");
      }
    }
    else if(instructions[i].field == 1){
      printf("opcode return : %d\n", instruction_to_opcode(instructions[i].a_or_c.c));
      op = instruction_to_opcode(instructions[i].a_or_c.c);
      printf("instruction is c\n");
    }
    OPCODE_TO_BINARY(op)(op);
    printf("op: %d\n", op);

  }
  fclose(hack);
}

opcode instruction_to_opcode(c_instruction instr){
  opcode op = 0;
  op |= (7 << 13);
  printf("%d", instr.a & 0x1);

  op |= (instr.a);
  op |= (instr.comp);
  op |= (instr.dest);
  op |= (instr.jump);

  //if(instr)

  return op;
}

char *strip(char *s){
  char s_new[strlen(s)+1];
  int i = 0;
  for (char *s2 = s; *s2; s2++){
    if (*s2=='/' && *(s2+1)=='/'){
      break;
    }
    else if (!isspace(*s2)){
      s_new[i++] = *s2;
    }
  }
  s_new[i] = '\0';
  strcpy(s, s_new);
  return s;
}

char *extract_label(const char *line, char* label){
  int i = 0;
  for (const char *s = line; *s; s++){
    if (*s=='(' || *s==')'){
      continue;
    }
    else{
      label[i++] = *s;
    }
  }
  label[i] = '\0';
  return label;
}

int is_Atype(const char *line){
  return line[0] == '@'; 
}

int is_label(const char *line){
  return line[0] == '(' && line[strlen(line)-1] == ')';
}

int is_Ctype(const char *line){
  if (!is_Atype(line) && !is_label(line)){
    return true;
  }
  else{
    return false;
  }
}

int parse(FILE * file, instruction *instructions){
  char line[MAX_LINE_LENGTH] = {0};
  instruction instr;
  unsigned int line_num = 0;
  unsigned int instr_num = 0;
  add_predefined_symbols();
  while (fgets(line, sizeof(line), file)){
    line_num++;
    if(instr_num > MAX_INSTRUCTION){
      exit_program(EXIT_TOO_MANY_INSTRUCTIONS, MAX_INSTRUCTION + 1);
    }
    strip(line); 
    if(!*line){
      continue;
    }

    char inst_type = ' ';
  
    if (is_Atype(line) == 1){
      inst_type = 'A';
      if (parse_A_instruction(line, &instr.a_or_c.a) == 0){
        exit_program(EXIT_INVALID_A_INSTR, line_num, line);
      }
      instr.field = A_type;
    }
    
    else if (is_label(line) == 1){
      inst_type = 'L';
      char label[MAX_LABEL_LENGTH] = {0};
      strcpy(line, extract_label(line, label));
      if(!isalpha(label[0])){
        exit_program(EXIT_INVALID_LABEL, line_num, line);
      }
      if(symtable_find(label) != NULL){
        exit_program(EXIT_SYMBOL_ALREADY_EXISTS, line_num, line);
      }
      symtable_insert(label, instr_num);
      continue;
    }
   
    else if (is_Ctype(line) == 1){
      inst_type = 'C';
      char tmp_line[MAX_LINE_LENGTH] = {0};
      strcpy(tmp_line, line);
      parse_C_instruction(tmp_line, &instr.a_or_c.c);
      if (instr.a_or_c.c.dest == DEST_INVALID){
        exit_program(EXIT_INVALID_C_DEST, line_num, line);
      }
      else if (instr.a_or_c.c.comp == COMP_INVALID){
        exit_program(EXIT_INVALID_C_COMP, line_num, line);
      }
      else if (instr.a_or_c.c.jump == JMP_INVALID){
        exit_program(EXIT_INVALID_C_JUMP, line_num, line);
      }
      instr.field = C_type;
    }
    
    printf("%c  %s\n", inst_type, line);
    instructions[instr_num++] = instr;
  }
  printf("here: %d\n", instr_num);
  return instr_num;
}
