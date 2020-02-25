#include <stdio.h>
#include <stdlib.h>

char code[20];              //temporary storage for the textual code
char prev[20];               //temporary storage, used to deal with retraction, lexical errors

int indexArr;               //index used to get character, from code or prev array, depending on whether it is positive or negative

int prevSize = 20;
int codeSize = 20;

FILE * start;
FILE * fp;

typedef struct pair{                //structure for storing token and lexeme to be passed to parser
    char* lexeme;                   
    char token[15];                 
} pair;

char * populateLexeme(int lexStart, int lexEnd); //stores the lexeme in memory and return a pointer to the same

char agetc();              //returns next character in the stream. Responsible for calling getStream when necessary. Should read from file directly if necesary.

FILE * getStream();        //populates arrays code and prev, updates indexArr, fp gets updated automatically, returns fp

pair getPair();           //returns pair, updates indexArr, whichArr


