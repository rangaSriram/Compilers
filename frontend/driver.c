#include <stdio.h>
#include <stdlib.h>
#include "driver.h"

int main(int argc, char * argv[]){
    int i = 1;
    while(i!=0){
        printf("\n\nPlease select an option:\n");
        printf("0 - to exit the program\n");
        printf("1 - To see comment free source code on the console\n");
        printf("2 - To see th list of tokens generated by the lexer\n");
        printf("3 - To see lexical and syntactical errors on the console and to get the parse tree in the textfile\n");
        printf("4 - To see time taken to verify lexical and syntactic correctness:\n\n");
        scanf("%d", &i);
        if(i==0)
            break;
        else if (i==1){
            FILE * ptr;
            ptr = fopen(argv[1], "r");
            char c = fgetc(ptr);
            while(c!=EOF){
                if(c=='*'){
                    c = fgetc(ptr);
                    if(c =='*'){
                        c = fgetc(ptr);
                        while(c!='\n'){
                            c = fgetc(ptr);
                        }
                        c = fgetc(ptr);
                    }
                    else{
                        printf("*");
                        printf("%c", c);
                        c = fgetc(ptr);
                    }
                }
                else{
                    printf("%c", c);
                    c = fgetc(ptr);
                }
                int i = 0;
            }
        }
        else if(i==2){
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
            printf("\nLine no, Lexeme, Token Name\n");
            while(ti.state!=60){
                //printf("Token %d: %s, %s, %d, %d\n", i+1, ti.name, ti.lexeme, ti.state, ti.lineNo);
                printf("%d: %s, %s\n", ti.lineNo, ti.lexeme, ti.name);
                free(ti.lexeme);                        
                i++;
                ti = getToken();
            }
        }
        else if(i==3){
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
            printf("\nPrinting all lexical errors\n");
            while(ti.state!=60){
                if(ti.state==61){
                    printf("%d: %s, %s\n", ti.lineNo, ti.lexeme, ti.name);
                }                        
                i++;
                free(ti.lexeme);
                ti = getToken();
            }
        }
        else if(i==4){
            printf("Not completed");
        }
    }
}

int fillBuffer(int n){
    for(int i = 0; i<20; i++){
        buff[n][i] = fgetc(file);
    }
}

int increment(){
    if(fp.index!=19){
        fp.index++;
    }
    else{
        fp.index = 0;
        fp.arrNum = (fp.arrNum+1)%2;
        fillBuffer(fp.arrNum);
    }
}

int retract(){
    if(fp.index!=0){
        fp.index--;
    }
    else{
        fp.index = 19;
        fp.arrNum = (fp.arrNum+1)%2;
        fseek(file, -20, SEEK_CUR);
    }
}

tokenInfo getToken(){
    //move fp to appropriate position
    //printf("\tRemoving white spaces\n");
    while(buff[bp.arrNum][fp.index]=='\n' || buff[bp.arrNum][fp.index]=='\t' || buff[bp.arrNum][fp.index]==' '){   //ignore white spaces, move fp, bp
        if(buff[bp.arrNum][fp.index]=='\n'){
            lineNo++;
        }
        if(fp.index!=19){
            fp.index++;
            bp.index++;
        }
        else{
            fp.index = 0;
            fp.arrNum = (bp.arrNum+1)%2;  //fill the other buffer and change pointers
            bp.index = 0;
            bp.arrNum = (bp.arrNum+1)%2;
            fillBuffer(bp.arrNum);
        }
    }
    //printf("\tDone removing white spaces\n");
    int state = 0;                              //start state
    char c = buff[bp.arrNum][bp.index];
    if(c==EOF){
        tokenInfo ti;
        ti.lexeme = eof;
        ti.lineNo = lineNo;
        //ti.state = getState(state);
        ti.state = 60;
        //ti.name = getName(state);
        ti.name = eof;                      //EOF has state 60
        return ti;
    }
    int tflag = 0;                              //used to know whether token is valid or not
    int bflag = 0;                              //used to know whether to get out of DFA or not
    //printf("\t");    
    while(c!=EOF){
        //printf("%c",c);
        switch(state){                          //DFA implementaion for NUM
            case 0:                             //not a final state
                if((c<='z' && c>='a') || (c<='Z' && c>='A')){           //various arrows in various if statements
                    state = 1;
                    tflag = 1;                  //final state is reached (state 1)
                    increment();
                }
                else if(c<='9' && c>='0'){
                    state = 2;
                    tflag = 1;
                    increment();
                }
                else if(c==':'){
                    state = 8;
                    tflag = 1;
                    increment();
                }
                else if(c=='*'){
                    state = 10;
                    tflag = 1;
                    increment();
                }
                else if(c=='<'){
                    state = 11;
                    tflag = 1;
                    increment();
                }
                else if(c=='>'){
                    state = 15;
                    tflag = 1;
                    increment();
                }
                else if(c=='.'){
                    state = 19;
                    tflag = 1;
                    increment();
                }
                else if(c=='+'){
                    state = 21;
                    tflag = 1;
                    increment();
                }
                else if(c=='-'){
                    state = 22;
                    tflag = 1;
                    increment();
                }
                else if(c=='/'){
                    state = 23;
                    tflag = 1;
                    increment();
                }
                else if(c=='='){
                    state = 24;
                    tflag = 1;
                    increment();
                }
                else if(c=='!'){
                    state = 26;
                    tflag = 1;
                    increment();
                }
                else if(c==';'){
                    state = 28;
                    tflag = 1;
                    increment();
                }
                else if(c==','){
                    state = 29;
                    tflag = 1;
                    increment();
                }
                else if(c=='['){
                    state = 30;
                    tflag = 1;
                    increment();
                }
                else if(c==']'){
                    state = 31;
                    tflag = 1;
                    increment();
                }
                else if(c=='('){
                    state = 32;
                    tflag = 1;
                    increment();
                }
                else if(c==')'){
                    state = 33;
                    tflag = 1;
                    increment();
                }
                else{                           //trap state
                    tokenInfo ti;
                    ti.lexeme = error;
                    ti.lineNo = lineNo;
                    ti.state = 61;
                    ti.name = error;
                    // while(c!='\n'){
                    //     increment();
                    //     c = buff[fp.arrNum][fp.index];
                    //     if(c==EOF){
                    //         break;
                    //     }
                    // }
                    // lineNo++;
                    // state = 0;
                    // tflag = 1;
                    increment();
                    bp.index = fp.index;
                    bp.arrNum = fp.arrNum;
                    return ti;
                }
                break;
            case 1:                             //it is a final state
                if((c<='z' && c>='a')||(c<='Z' && c>='A')||(c<='9' && c>='0')||c=='_'){
                    state = 1;
                    tflag = 1;                  //final state is reached (state 1)
                    increment();
                }
                else{                           //for others arrow
                    bflag = 1;                 
                }
                break;
            case 2:                             //it is a final state
                if(c<='9' && c>='0'){
                    state = 2;
                    tflag = 1;                  //final state is reached (state 1)
                    increment();
                }
                else if(c=='.'){
                    state = 3;
                    tflag = 0;                  //not a valid token anymore
                    increment();
                }
                else{                           //for others arrow
                    bflag = 1;                  
                }
                break;
            case 3:                             //not a final state
                if(c<='9' && c>='0'){
                    state = 4;
                    tflag = 1;
                    increment();
                }
                else if(c=='.'){
                    state = 7;
                    tflag = 1;
                    increment();
                }
                else{                           //trap state
                    tokenInfo ti;
                    ti.lexeme = error;
                    ti.lineNo = lineNo;
                    ti.state = 61;
                    ti.name = error;
                    // while(c!='\n'){
                    //     increment();
                    //     c = buff[fp.arrNum][fp.index];
                    //     if(c==EOF){
                    //         break;
                    //     }
                    // }
                    // lineNo++;
                    // state = 0;
                    // tflag = 1;
                    increment();
                    bp.index = fp.index;
                    bp.arrNum = fp.arrNum;
                    return ti;
                }
                break;
            case 4:                             //it is a final state
                if(c<='9' && c>='0'){
                    state = 4;
                    tflag = 1;                  
                    increment();
                }
                else if(c=='e' || c=='E'){
                    state = 5;
                    tflag = 0;
                    increment();
                }
                else{                           //for others arrow
                    bflag = 1;                  
                }
                break;
            case 5:                             //not a final state
                if(c<='9' && c>='0'){
                    state = 34;
                    tflag = 1;
                    increment();                
                }
                else if(c=='+' || c=='-'){
                    state = 6;
                    tflag = 0;
                    increment();
                }
                else{                           //trap state
                    tokenInfo ti;
                    ti.lexeme = error;
                    ti.lineNo = lineNo;
                    ti.state = 61;
                    ti.name = error;
                    // while(c!='\n'){
                    //     increment();
                    //     c = buff[fp.arrNum][fp.index];
                    //     if(c==EOF){
                    //         break;
                    //     }
                    // }
                    // lineNo++;
                    // state = 0;
                    // tflag = 1;
                    increment();
                    bp.index = fp.index;
                    bp.arrNum = fp.arrNum;
                    return ti;
                }
                break;
            case 6:                             //it is a non final state
                if(c<='9' && c>='0'){
                    state = 34;
                    tflag = 1;                  
                    increment();
                }
                else{                           //for others arrow
                    tokenInfo ti;
                    ti.lexeme = error;
                    ti.lineNo = lineNo;
                    ti.state = 61;
                    ti.name = error;
                    // while(c!='\n'){
                    //     increment();
                    //     c = buff[fp.arrNum][fp.index];
                    //     if(c==EOF){
                    //         break;
                    //     }
                    // }
                    // lineNo++;
                    // state = 0;
                    // tflag = 1;
                    increment();
                    bp.index = fp.index;
                    bp.arrNum = fp.arrNum;
                    return ti;                  
                }
                break;
            case 7:                             //it is a final state
                bflag = 1;
                retract();
                retract();
                break;
            case 8:                             //it is a final state
                if(c=='='){
                    state = 9;
                    tflag = 1;                  
                    increment();
                }
                else{                           //for others arrow
                    bflag = 1;                  
                }
                break;
            case 9:                             //it is a final state
                bflag = 1;
                break;
            case 10:                            //comment eater
                if(c!='*'){
                    bflag = 1;
                }
                else{
                    while(c!='\n'){
                        increment();
                        c = buff[fp.arrNum][fp.index];
                        if(c==EOF){
                            tokenInfo ti;
                            ti.lexeme = eof;
                            ti.lineNo = lineNo;
                            ti.state = 60;
                            ti.name = eof;                      //EOF has state 60
                            return ti;
                        }
                    }
                    lineNo++;
                    state = 0;
                    tflag = 1;
                    increment();
                    bp.index = fp.index;
                    bp.arrNum = fp.arrNum;
                    while(buff[bp.arrNum][fp.index]=='\n' || buff[bp.arrNum][fp.index]=='\t' || buff[bp.arrNum][fp.index]==' '){   //ignore other white spaces, move fp, bp
                        if(buff[bp.arrNum][fp.index]=='\n'){
                            lineNo++;
                        }
                        if(fp.index!=19){
                            fp.index++;
                            bp.index++;
                        }
                        else{
                            fp.index = 0;
                            fp.arrNum = (bp.arrNum+1)%2;  //fill the other buffer and change pointers
                            bp.index = 0;
                            bp.arrNum = (bp.arrNum+1)%2;
                            fillBuffer(bp.arrNum);
                        }
                    }
                }
                break;
            case 11:
                if(c=='='){
                    state = 12;
                    tflag = 1;
                    increment();
                }
                if(c=='<'){
                    state = 13;
                    tflag = 1;
                    increment();
                }
                else{
                    bflag = 1;
                }
                break;
            case 12:
                bflag = 1;
                break;
            case 13:
                if(c=='<'){
                    state = 14;
                    tflag = 1;
                    increment();
                }
                else{
                    bflag = 1;
                }
                break;
            case 14:
                bflag = 1;
                break;
            case 15:
                if(c=='='){
                    state = 16;
                    tflag = 1;
                    increment();
                }
                else if(c=='>'){
                    state = 17;
                    tflag = 1;
                    increment();
                }
                else{
                    bflag = 1;
                }
                break;
            case 16:
                bflag = 1;
                break;
            case 17:
                if(c=='>'){
                    state = 18;
                    tflag = 1;
                    increment();
                }
                else{
                    bflag = 1;
                }
                break;
            case 18:
                bflag = 1;
                break;
            case 19:
                if(c=='.'){
                    state = 20;
                    tflag = 1;
                    increment();
                }
                else{
                    tokenInfo ti;
                    ti.lexeme = error;
                    ti.lineNo = lineNo;
                    ti.state = 61;
                    ti.name = error;
                    // while(c!='\n'){
                    //     increment();
                    //     c = buff[fp.arrNum][fp.index];
                    //     if(c==EOF){
                    //         break;
                    //     }
                    // }
                    // lineNo++;
                    // state = 0;
                    // tflag = 1;
                    increment();
                    bp.index = fp.index;
                    bp.arrNum = fp.arrNum;
                    return ti;
                }
                break;
            case 20:
                bflag = 1;
                break;
            case 21:
                bflag = 1;
                break;
            case 22:
                bflag = 1;
                break;
            case 23:
                bflag = 1;
                break;
            case 24:
                if(c=='='){
                    state = 25;
                    tflag = 1;
                    increment();
                }
                else{
                    tokenInfo ti;
                    ti.lexeme = error;
                    ti.lineNo = lineNo;
                    ti.state = 61;
                    ti.name = error;
                    // while(c!='\n'){
                    //     increment();
                    //     c = buff[fp.arrNum][fp.index];
                    //     if(c==EOF){
                    //         break;
                    //     }
                    // }
                    // lineNo++;
                    // state = 0;
                    // tflag = 1;
                    increment();
                    bp.index = fp.index;
                    bp.arrNum = fp.arrNum;
                    return ti;
                }
                break;
            case 25:
                bflag = 1;
                break;
            case 26:
                if(c=='='){
                    state = 27;
                    tflag = 1;
                    increment();
                }
                else{
                    tokenInfo ti;
                    ti.lexeme = error;
                    ti.lineNo = lineNo;
                    ti.state = 61;
                    ti.name = error;
                    // while(c!='\n'){
                    //     increment();
                    //     c = buff[fp.arrNum][fp.index];
                    //     if(c==EOF){
                    //         break;
                    //     }
                    // }
                    // lineNo++;
                    // state = 0;
                    // tflag = 1;
                    increment();
                    bp.index = fp.index;
                    bp.arrNum = fp.arrNum;
                    return ti;
                }
                break;
            case 27:
                bflag = 1;
                break;
            case 28:
                bflag = 1;
                break;
            case 29:
                bflag = 1;
                break;
            case 30:
                bflag = 1;
                break;
            case 31:
                bflag = 1;
                break;
            case 32:
                bflag = 1;
                break;
            case 33:
                bflag = 1;
                break;
            case 34:                             //it is a final state
                if(c<='9' && c>='0'){
                    state = 34;
                    tflag = 1;                  
                    increment();
                }
                else{                           //for others arrow
                    bflag = 1;                  
                }
                break;
            
        }
        if(bflag==1){
            break;
        }
        else{
            c = buff[fp.arrNum][fp.index];
        }
    }
    //printf("\n\t tflag = %d, bflag = %d\n", tflag, bflag);
    if(c==EOF){                     
        if(tflag==0){                   //if EOF is reached with an incomplete token
            tokenInfo ti;
            ti.lexeme = error;
            ti.lineNo = lineNo;
            ti.state = 61;
            ti.name = error;
            return ti;
        }
        // else{                           //else, retract(different from non EOF retract)
        //     if(fp.index!=0){
        //         fp.index--;
        //     }
        //     else{
        //         fp.index = 19;
        //         fp.arrNum = (fp.arrNum+1)%2;
        //     }
        // }
    }

    //printf("\tRetuning token:");
    //return correct token
    if(bp.arrNum==0 && fp.arrNum==0){
        int len = fp.index-bp.index;
        char * token = malloc(sizeof(char)*(len+1));
        for(int i = 0;i<len; i++){
            token[i] = buff[0][bp.index + i];
        }
        token[len] = '\0';
        //printf("%s\n", token);
        // if(fp.index==19){
        //     fp.index = 0;
        //     fp.arrNum = (fp.arrNum+1)%2;
        //     bp.index = 0;
        //     bp.arrNum = fp.arrNum;
        //     fillBuffer(bp.arrNum);
        // }
        // else{
        //     fp.index++;
        bp.index = fp.index;
        bp.arrNum = fp.arrNum;
        // }
        tokenInfo ti;
        if(state == 1){
            int n = isKeyword(token);           //returns -1 if token is not a keyword
            if(n!=-1){
                ti.lexeme = token;
                ti.lineNo = lineNo;
                if(n==11 || n==12 || n==13){
                    ti.state = 1059;
                }
                else{
                    ti.state = 1000 + n;
                }
                ti.name = keywordTokens[n];
                return ti;
            }
        }
        ti.lexeme = token;
        ti.lineNo = lineNo;
        ti.state = states[state];
        ti.name = names[state];
        return ti;
    }
    if(bp.arrNum==1 && fp.arrNum==1){
        int len = fp.index-bp.index;
        char * token = malloc(sizeof(char)*(len+1));
        for(int i = 0;i<len; i++){
            token[i] = buff[1][bp.index + i];
        }
        token[len] = '\0';
        //printf("%s\n", token);
        // if(fp.index==19){
        //     fp.index = 0;
        //     fp.arrNum = (fp.arrNum+1)%2;
        //     bp.index = 0;
        //     bp.arrNum = fp.arrNum;
        //     fillBuffer(bp.arrNum);
        // }
        // else{
        //     fp.index++;
            bp.index = fp.index;
            bp.arrNum = fp.arrNum;
        // }
        tokenInfo ti;
        if(state == 1){
            int n = isKeyword(token);           //returns -1 if token is not a keyword
            if(n!=-1){
                ti.lexeme = token;
                ti.lineNo = lineNo;
                if(n==11 || n==12 || n==13){
                    ti.state = 1059;
                }
                else{
                    ti.state = 1000 + n;
                }
                ti.name = keywordTokens[n];
                return ti;
            }
        }
        ti.lexeme = token;
        ti.lineNo = lineNo;
        ti.state = states[state];
        ti.name = names[state];
        return ti;
    }
    if(bp.arrNum==0 && fp.arrNum==1){
        int len = fp.index+20-bp.index;
        char * token = malloc(sizeof(char)*(len+1));
        for(int i = 0; bp.index+i<20; i++){
            token[i] = buff[0][bp.index + i];
        }
        for(int i=0; i<=fp.index; i++){
            token[20-bp.index+i] = buff[1][i];
        }
        token[len] = '\0';
        //printf("%s\n", token);
        // if(fp.index==19){
        //     fp.index = 0;
        //     fp.arrNum = (fp.arrNum+1)%2;
        //     bp.index = 0;
        //     bp.arrNum = fp.arrNum;
        //     fillBuffer(bp.arrNum);
        // }
        // else{
        //     fp.index++;
            bp.index = fp.index;
            bp.arrNum = fp.arrNum;
        // }
        tokenInfo ti;
        if(state == 1){
            int n = isKeyword(token);           //returns -1 if token is not a keyword
            if(n!=-1){
                ti.lexeme = token;
                ti.lineNo = lineNo;
                if(n==11 || n==12 || n==13){
                    ti.state = 1059;
                }
                else{
                    ti.state = 1000 + n;
                }
                ti.name = keywordTokens[n];
                return ti;
            }
        }
        ti.lexeme = token;
        ti.lineNo = lineNo;
        ti.state = states[state];
        ti.name = names[state];
        return ti;
    }
    if(bp.arrNum==1 && fp.arrNum==0){
        int len = fp.index+20-bp.index;
        char * token = malloc(sizeof(char)*(len+1));
        for(int i = 0; bp.index+i<20; i++){
            token[i] = buff[1][bp.index + i];
        }
        for(int i=0; i<=fp.index; i++){
            token[20-bp.index+i] = buff[0][i];
        }
        token[len] = '\0';
        //printf("%s\n", token);
        // if(fp.index==19){
        //     fp.index = 0;
        //     fp.arrNum = (fp.arrNum+1)%2;
        //     bp.index = 0;
        //     bp.arrNum = fp.arrNum;
        //     fillBuffer(bp.arrNum);
        // }
        // else{
        //     fp.index++;
            bp.index = fp.index;
            bp.arrNum = fp.arrNum;
        // }
        tokenInfo ti;
        if(state == 1){
            int n = isKeyword(token);           //returns -1 if token is not a keyword
            if(n!=-1){
                ti.lexeme = token;
                ti.lineNo = lineNo;
                if(n==11 || n==12 || n==13){
                    ti.state = 1059;
                }
                else{
                    ti.state = 1000 + n;
                }
                ti.name = keywordTokens[n];
                return ti;
            }
        }
        ti.lexeme = token;
        ti.lineNo = lineNo;
        ti.state = states[state];
        ti.name = names[state];
        return ti;
    }
}

int isKeyword(char * token){                    //tells us if the token is a keyword (returns -1 if not). Only 34 keywords as of now!
    for(int i = 0; i<34; i++){
        int j=0;
        while(token[j]!='\0' && keywordLexemes[i][j]!='\0'){
            if(token[j]==keywordLexemes[i][j]){
                j++;
            }
            else{
                break;
            }
        }
        if(token[j]=='\0' && keywordLexemes[i][j]=='\0' && j!=0){
            return i;
        }
    }
    return -1;
}