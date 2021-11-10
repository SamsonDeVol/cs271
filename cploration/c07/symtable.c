#include "symtable.h"


int hash(char* str) {
  unsigned long hash = 5381;
  int c;

  while ((c = *str++)) 
    hash = ((hash << 5) + hash) + c;
  
  return hash % SYMBOL_TABLE_SIZE;

};

void insert(char* name, hack_addr addr){
  struct Symbol *item = (struct Symbol*) malloc(sizeof(struct Symbol));
  item->addr = addr;
  item->name = name;

  int hashIndex = hash(name);

  while(hashArray[hashIndex] != NULL && hashArray[hashIndex]->name != NULL) {
    ++hashIndex;
    hashIndex %= SYMBOL_TABLE_SIZE;
  }
  hashArray[hashIndex] = item;
}

void display_table() {
  int i = 0;
  for(i = 0; i< SYMBOL_TABLE_SIZE; i++) {
    if(hashArray[i] != NULL)
      printf(" (%s,%d)", hashArray[i]->name, hashArray[i]->addr);
    else
      printf(" ~~ ");
  }
  printf("\n");
}


struct Symbol *find(char* name) {
  int hashIndex = hash(name);

  while(hashArray[hashIndex] != NULL) {

    if(hashArray[hashIndex]->name == name)
      return hashArray[hashIndex];

    ++hashIndex;

    hashIndex %= SYMBOL_TABLE_SIZE;

  }
  return NULL;
};
