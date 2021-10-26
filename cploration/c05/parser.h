#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#define MAX_LINE_LENGTH 200

char *strip(char *s);
void parse(FILE * file);

int is_Atype(const char *);
int is_label(const char *);
int is_Ctype(const char *);