#include "parser.h"
#include "error.h"
#include "symtable.h"

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
  printf("inital token: %s\n", token);
  printf("line: %s\n", line);
  token = strtok(line, ";");
  temp = token;
  printf("strcomp: %d\n", str_to_compid("M"));
  token = strtok(NULL, ";");
  
  instr->jump = str_to_jumpid(token);
  token = strtok(temp, "=");
  
  instr->dest = str_to_destid(token);
  
  token = strtok(NULL, "=");
  
  if(token != NULL){
    printf("input token: %d\n", str_to_compid(token));
    instr->comp =str_to_compid(token);

    
  }
  instr->a = (instr->comp < 0) ? (1) : (0);
  //printf("jump: %hd\n", instr->jump);
  //printf("dest: %hd\n", instr->dest);
  //printf("comp: %d\n", instr->comp);
  //printf("a: %hd\n", instr->a);


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

void parse(FILE * file){
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
      parse_C_instruction(line, &instr.a_or_c.c);
    }
    printf("%c  %s\n", inst_type, line);
    instr_num++;
  }
  
}