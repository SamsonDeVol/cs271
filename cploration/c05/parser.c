#include "parser.h"
#define MAX_LINE_LENGTH 200

char *strip(char *s){
  char s_new[strlen(s)+1];
  int i = 0;
  for (char *s2 = s; *s2; s2++){
    if (*s2=='/' && *(s+1)=='/'){
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
 
 while (fgets(line, sizeof(line), file)){
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
    }
    else if (is_Ctype(line) == 1){
      inst_type = 'C';
    }
    
    printf("%c  %s\n", inst_type, line);
  }
}
