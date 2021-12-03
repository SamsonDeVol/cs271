#include "parser.h"
#include "error.h"
#include "hack.h"
#include "symtable.h"

#define MAX_INSTRUCTION_COUNT 30000

int main(int argc, const char *argv[]){

instruction *instructions = malloc(MAX_INSTRUCTION_COUNT * sizeof(instruction));

if(argc != 2){
    // incorrect number of arguments
    exit_program(EXIT_INCORRECT_ARGUMENTS, argv[0]);
}

FILE *fin = fopen(argv[1], "r");
 
if(fin == NULL){
    exit_program(EXIT_CANNOT_OPEN_FILE, argv[1]);
}
int num_instructions = parse(fin, instructions);

fclose(fin);
assemble(argv[1], instructions, num_instructions);
free(instructions);
}
