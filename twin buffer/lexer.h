#ifndef LEXER_H
#define LEXER_H
#include "lexerDef.h"

tokenInfo getToken();
int fillBuffer(int n);
int increment();
int retract();
int isKeyword(char * token);
void lexerInitialize();
#endif