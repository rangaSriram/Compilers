#include <stdlib.h>
#include <stdio.h>
#include "lexer.h"
#include "parser.h"

int main(){
    lexerInitialize();
    bp.index = 0;
    bp.arrNum = 0;
    fp.index = 0;
    fp.arrNum = 0;
    lineNo = 1;
    start = fopen("text.txt", "r");
    file = start;
    for(int i = 0; i<20; i++){                  //filling buffer only row 0
        buff[0][i] = fgetc(file);
    }
    tokenInfo ti = getToken();
    int i = 0;
    while(ti.state!=60){
        //printf("Token %d: %s, %s, %d, %d\n", i+1, ti.name, ti.lexeme, ti.state, ti.lineNo);
        printf("%d: %s, %s\n", ti.lineNo, ti.lexeme, ti.name);
        free(ti.lexeme);                        
        i++;
        ti = getToken();
    }
}