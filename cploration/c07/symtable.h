#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdint.h>

#define SYMBOL_TABLE_SIZE 100

typedef int16_t hack_addr;

struct Symbol {
  char* name;
  hack_addr addr;
};

struct Symbol* hashArray[SYMBOL_TABLE_SIZE];
struct Symbol* dummyItem;
struct Symbol* item;

int hash(char *str);
struct Symbol *find(char *key);
void insert(char* key, hack_addr addr);
void display_table();