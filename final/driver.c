//BATCH NUMBER 49
//RANGA SRIRAM 2017A7PS0047P
//RAYAPATI YASWANTH KUMAR 2017A7PS0038P
//KATTA SIVA KUMAR 2017A7A7PS0078P

#include <stdlib.h>
#include <stdio.h>
#include "lexer.h"
#include "parser.h"
#include <time.h>

int main(int argc, char * argv[]){
    int i = 1;
    lexerInitialize();
    parserInitialize();
    while(i!=0){
        printf("\n\nPlease select an option:\n");
        printf("0 - to exit the program\n");
        printf("1 - To see comment free source code on the console\n");
        printf("2 - To see th list of tokens generated by the lexer\n");
        printf("3 - To see lexical and syntactical errors on the console and to get the parse tree in the textfile\n");
        printf("4 - To see time taken to verify lexical and syntactic correctness:\n\n");
        scanf("%d", &i);
        printf("\n");
        if(i==0){
            printf("Closing program\n");
            break;
        }
        else if (i==1){
            FILE * ptr;
            ptr = fopen(argv[1], "r");
            uncommentedPrint(ptr);
        }
        else if(i==2){
            bp.index = 0;
            bp.arrNum = 0;
            fp.index = 0;
            fp.arrNum = 0;
            lineNo = 1;
            start = fopen(argv[1], "r");
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
            start = fopen(argv[1], "r");
            file = start;
            for(int i = 0; i<20; i++){                  //filling buffer only row 0
                buff[0][i] = fgetc(file);
            }
            tokenInfo ti = getToken();
            int i = 0;
            printf("\nLexical errors:\n\nLine number :\terror\n");
            while(ti.state!=60){
                //printf("Token %d: %s, %s, %d, %d\n", i+1, ti.name, ti.lexeme, ti.state, ti.lineNo);
                if(ti.state == 61){
                    printf("%d : \t%s\n", ti.lineNo, ti.lexeme);
                    i++;
                }
                free(ti.lexeme);                        
                ti = getToken();
            }
            if(i==0){
                printf("\n\t\tNo lexical errors were found\n\n");
            }
            // lexerInitialize();
            // parserInitialize();

            // bp.index = 0;
            // bp.arrNum = 0;
            // fp.index = 0;
            // fp.arrNum = 0;
            // lineNo = 1;
            // start = fopen("testcase.txt", "r");
            // file = start;
            // for(int i = 0; i<20; i++){                  //filling buffer only row 0
            //     buff[0][i] = fgetc(file);
            // }

            // grammar_Generator();
            // modifyGrammar();
            // Parse_Table_create();
            //parseInputSourceCode("test", ptable);
        }
        else if(i==4){

            clock_t    start_time, end_time;

            double total_CPU_time, total_CPU_time_in_seconds;

            start_time = clock();
                bp.index = 0;
                bp.arrNum = 0;
                fp.index = 0;
                fp.arrNum = 0;
                lineNo = 1;
                start = fopen(argv[1], "r");
                file = start;
                for(int i = 0; i<20; i++){                  //filling buffer only row 0
                    buff[0][i] = fgetc(file);
                }
                tokenInfo ti = getToken();
                int i = 0;
                printf("\nLine no, Lexeme, Token Name\n");
                while(ti.state!=60){
                    //printf("Token %d: %s, %s, %d, %d\n", i+1, ti.name, ti.lexeme, ti.state, ti.lineNo);
                    //printf("%d: %s, %s\n", ti.lineNo, ti.lexeme, ti.name);
                    free(ti.lexeme);                        
                    i++;
                    ti = getToken();
                }

            end_time = clock();

            total_CPU_time  =  (double) (end_time - start_time);

            total_CPU_time_in_seconds =   total_CPU_time / CLOCKS_PER_SEC;

            printf("Total time in ticks is %lf, in seconds is %lf\n", total_CPU_time, total_CPU_time_in_seconds);
        }
    }
}


// int main(){
//     lexerInitialize();
//     parserInitialize();
//     bp.index = 0;
//     bp.arrNum = 0;
//     fp.index = 0;
//     fp.arrNum = 0;
//     lineNo = 1;
//     start = fopen("text.txt", "r");
//     file = start;
//     for(int i = 0; i<20; i++){                  //filling buffer only row 0
//         buff[0][i] = fgetc(file);
//     }
//     grammar_Generator();
//     modifyGrammar();
//     FILE *fp1;
//     fp1 = fopen("test1.txt", "w+");
//     int i, j;
//     for (i=0; i<NO_OF_RULES; i++) {
//         for (j=0; j<MAX_RIGHTSIDE; j++) {
//             if (GR[i][j].state != -100) 
//                 fprintf(fp1, "%d ", GR[i][j].state);
//         }
//         fprintf(fp1, "\n");
//     }
//     fclose(fp1);
//     //removeComments("t3.txt", "test");
//     //grammarGenerator();
//     Parse_Table_create();
//     parseInputSourceCode("test", ptable);
//     // tokenInfo ti = getToken();
//     // int i = 0;
//     // while(ti.state!=60){
//     //     //printf("Token %d: %s, %s, %d, %d\n", i+1, ti.name, ti.lexeme, ti.state, ti.lineNo);
//     //     printf("%d: %s, %s\n", ti.lineNo, ti.lexeme, ti.name);
//     //     free(ti.lexeme);                        
//     //     i++;
//     //     ti = getToken();
//     // }
// }