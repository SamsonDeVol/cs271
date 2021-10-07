// Samson DeVol, cs271, cploration 2

#include <stdio.h>
#include <string.h>
#define MAX_LIMIT 100

int main(){
/** WARMUP **/
// declare a string with value
char hello[] = "Hello";
// declare an empty string
char name[MAX_LIMIT];

// prompt user
printf("What is your name? ");

// read in a string from user and save in variable
// [^\n] means to discard the newline character
scanf("%[^\n]s", name);

// print out "hello <name>"
printf("%s %s!\n\n", hello, name);
    
/** Exercise 1 **/
// declare a new empty string 
char welcome[MAX_LIMIT];
// copy hello variable to welcome variable
strcpy(welcome, hello);
// concatenate an empty single space into welcome
strcat(welcome, " ");
// concatenate the name variable into the welcome variable
strcat(welcome, name);
// print the welcome variable followed by a newline
printf("%s!\n", welcome);

/**Exercise 2 **/
int length;
// determine the length of the name variable
for(int i=0; i<strlen(name); i++){
    length = i+1;
}
// print length of the name variable
printf("Your name is %i characters long.\n", length);

/** Exercise 3 **/
// paste in variable declaration
char prof[8] = {'P','a','t','r','i','c','k','\0'};
// compare the strings
int alphabetical = strcmp(name, prof);
// if name occurs before prof
if(alphabetical<0){
    printf("%s is before %s.\n", name, prof);
}
// if name occurs after prof
if(alphabetical>0){
    printf("%s is after %s.\n", name, prof);
}
// if name is the same as prof
if(alphabetical==0){
    printf("%s is %s.\n", name, prof);
}
}
