#include "parser.h"
#include "error.h"
#include "symtable.h"

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
  unsigned int line_num = 0;
  unsigned int instr_num = 0;

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
    }
    printf("%c  %s\n", inst_type, line);
    instr_num++;
  }
  
}
