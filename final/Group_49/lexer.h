//BATCH NUMBER 49
//RANGA SRIRAM 2017A7PS0047P
//RAYAPATI YASWANTH KUMAR 2017A7PS0038P
//KATTA SIVA KUMAR 2017A7A7PS0078P

#ifndef LEXER_H
#define LEXER_H
#include "lexerDef.h"

tokenInfo getToken();
int fillBuffer(int n);
int increment();
int retract();
int isKeyword(char * token);
void lexerInitialize();
void uncommentedPrint(FILE * ptr);
#endif