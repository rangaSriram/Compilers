#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "lexer.h"

//start and fp must initialized in driver, getStream must be called once

int main(){
    start = fopen("test.txt", "r");
    fp = start;
    getStream();
    pair p1;
    p1 = getPair();
    // while(strcmp(p1.token, "EOF")){
    //     printf("p1: %s, %s\n", p1.lexeme, p1.token);
    //     p1 = getPair(start);  
    // }
    for(int i = 0; i<20; i++){
        printf("p1: %s, %s\n", p1.lexeme, p1.token);
        p1 = getPair(start);  
    }
    printf("\nEND\n");
}

FILE * getStream(){                         //have to deal with EOF yet
    if(start!=fp){
        for(int i = 0; i<prevSize; i++){
            prev[i] = code[codeSize-5+i];
        }
    }    
    for(int i = 0; i<codeSize; i++){
        code[i] = fgetc(fp);
    }
    indexArr = 0;
    return fp;
}

char agetc(){
    if(indexArr>=0){
        indexArr++;
        return code[indexArr];
    }
    else{
        indexArr++;
        return prev[5+indexArr];
    }
    if(indexArr>=codeSize){
        getStream();
    }
}


pair getPair(){
    int lexStart = indexArr, lexEnd;
    char c;
    c = agetc();
    pair result;
    if(c == EOF){                       //check for empty file
        strcpy(result.token, "EOF");
        result.lexeme = NULL;
        return result;
    }
    while(c == '\n' || c == ' ' || c == '\t'){      //ignoring white spaces, while keeping a check for EOF
        c = agetc();
        if(c == EOF){
            strcpy(result.token, "EOF");
            result.lexeme = NULL;
            return result;
        }
    }
    int state = 0;
    lexStart = indexArr;
    while(c!=EOF){
        switch(state){                          //DFA implementaion for NUM
            case 0: 
                if(c<='9' && c>='0'){
                    state = 1;
                }
                else{
                    strcpy(result.token, "ERROR");
                    result.lexeme = NULL;
                    indexArr--;       //retract 1
                    return result;
                }
                break;
            case 1:
                if(c<='9' && c>='0'){
                    state = 1;
                }
                else{
                    strcpy(result.token, "NUM");
                    result.lexeme = populateLexeme(lexStart, indexArr-1);
                    indexArr--;       //retract 1
                    return result;
                }
                break;
        }
        c = agetc();
    }
    if(state==1){                           //If EOF is reached while reading a token
        strcpy(result.token, "NUM");
        result.lexeme = populateLexeme(lexStart, indexArr-1);
        return result;
    }
    else{
        indexArr = lexStart;
        strcpy(result.token, "ERROR");
        result.lexeme = NULL;
        return result;
    }
}

char * populateLexeme(int lexStart, int lexEnd){
    char * ptr = malloc((lexEnd-lexStart+1)*sizeof(char));
    for(int i = 0; i<lexEnd-lexStart+1; i++){
        if(lexEnd+i<0){
            ptr[i] = prev[lexEnd+i];
        }
        else{
            ptr[i] = code[lexEnd+i];
        }     
    }
    return ptr;
}
