#include <stdio.h>
#include <string.h>

typedef struct pair{
    char lexeme[20];                    //token length restricted to 20 characters
    char token[20];
} pair;

pair getPair(FILE * ptr);

int main(){

    FILE *ptr = fopen("test.txt", "r");
    pair p1;
    p1 = getPair(ptr);
    while(strcmp(p1.token, "")){
        printf("p1: %s, %s\n", p1.lexeme, p1.token);
        p1 = getPair(ptr);  
    }
    printf("\nEND\n");
}

pair getPair(FILE * ptr){            //gives token pairs one at a time. Returns an empty string for token when EOF in reached
    char lexeme[21];
    char c;
    c = fgetc(ptr);
    pair result;
    if(c == EOF){                       //check for empty file
        strcpy(result.token, "");
        strcpy(result.lexeme, "");
        return result;
    }
    while(c == '\n' || c == ' ' || c == '\t'){      //ignoring white spaces, while keeping a check for EOF
        c = fgetc(ptr);
        if(c == EOF){
            strcpy(result.token, "");
            strcpy(result.lexeme, "");
            return result;
        }
    }
    int state = 0;
    int i = 0;
    while(c!=EOF){
        switch(state){                          //DFA implementaion for NUM
            case 0: 
                if(c<='9' && c>='0'){
                    lexeme[i] = c;
                    i++;
                    state = 1;
                }
                else{
                    lexeme[i] = '\0';
                    strcpy(result.token, "");
                    strcpy(result.lexeme, "");
                    fseek(ptr, -1, SEEK_CUR);       //retract 1
                    return result;
                }
                break;
            case 1:
                if(c<='9' && c>='0'){
                    lexeme[i] = c;
                    i++;
                    state = 1;
                }
                else{
                    lexeme[i] = '\0';
                    strcpy(result.token, "NUM");
                    strcpy(result.lexeme, lexeme);
                    fseek(ptr, -1, SEEK_CUR);
                    return result;
                }
                break;
        }
        c = fgetc(ptr);
    }
    if(state==1){                           //If EOF is reached while reading a token
        lexeme[i] = '\0';
        strcpy(result.token, "NUM");
        strcpy(result.lexeme, lexeme);
        return result;
    }
    else{
        lexeme[i] = '\0';
        strcpy(result.token, "");
        strcpy(result.lexeme, lexeme);
        return result;
    }
}
