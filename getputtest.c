#include <stdio.h>
#include <string.h>

int main(){
    FILE * ptr = fopen("getput.txt", "r");   
    printf("%c\n",fgetc(ptr));
    fseek(ptr, -1, SEEK_CUR);
    printf("%c\n",fgetc(ptr));
    printf("%c\n",fgetc(ptr));


}