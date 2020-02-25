#include <stdlib.h>
#include <stdio.h>

typedef struct ptr{
    int index;
    int arrNum;
} ptr;

typedef struct tokenInfo{
    char * name;
    char * lexeme;
    int state;
    int lineNo;
} tokenInfo;

char buff[2][20];
int lineNo;

char* names[35] = {"", "ID", "NUM", "", "RNUM", "", "", "NUM", "COLON", "ASSIGNOP", "MUL", "LT", "LE", "DEF", "DRIVERDEF", "GT", "GE", "ENDDEF", "DRIVERENDDEF", "", "RANGEOP", "PLUS", "MINUS", "DIV", "", "EQ", "", "NE", "SEMICOL", "COMMA", "SQBO", "SQBC", "BO", "BC", "RNUM"};
int states[35] = {0, 1059, 1057, 0, 1058, 0, 0, 1057, 1047, 1051, 1035, 1037, 1038, 1043, 1044, 1040, 1039, 1045, 1046, 0, 1048, 1033, 1034, 1036, 0, 1041, 0, 1042, 1049, 1050, 1052, 1053, 1054, 1055, 1058};

char * keywordLexemes[34] = {"integer", "real", "boolean", "of", "array", "start", "end", "declare", "module", "driver", "program", "record", "tagged", "union", "get_value", "print", "use", "with", "parameters", "true", "false", "takes", "input", "returns", "AND", "OR", "for", "in", "switch", "case", "break", "default", "while", "$"};
char * keywordTokens[34] = {"INTEGER", "REAL", "BOOLEAN", "OF", "ARRAY", "START", "END", "DECLARE", "MODULE", "DRIVER", "PROGRAM", "ID", "ID", "ID", "GET_VALUE", "PRINT", "USE", "WITH", "PARAMETERS", "TRUE", "FALSE", "TAKES", "INPUT", "RETURNS", "AND", "OR", "FOR", "IN", "SWITCH", "CASE", "BREAK", "DEFAULT", "WHILE", "$"};

ptr bp, fp;

FILE * file;                                    //current file pointer
FILE * start;                                   //starting file pointer

char error[15] = "error";
char eof[15] = "EOF";

tokenInfo getToken();

int fillBuffer(int n);

int increment();

int retract();

int isKeyword(char * token);