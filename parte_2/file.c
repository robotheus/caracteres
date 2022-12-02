#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "file.h"

FILE *fileInput1, *fileInput2, *fileOutput;

void open_file(char argv1[], char argv2[]){
    fileInput1 = fopen(argv1, "r");
    fileInput2 = fopen(argv2, "r");
    fileOutput = fopen("saida.txt", "w");

    if(fileInput1 == NULL || fileInput2 == NULL) printf("ERRO AO ABRIR O ARQUIVO.\n");
}

void read_file_text(char *palavra, char *texto){
    strcpy(texto, "\0");
    strcpy(palavra, "\0");

    while (fscanf(fileInput1, "%s", palavra) != EOF){
        strcat(texto, palavra);
        strcat(texto, " ");
        strcpy(palavra, "\0");
    }

    strcat(texto, "\0");
}

int read_file_pattern(char *padrao){
    int x;
    strcpy(padrao, "\0");

    x = fscanf(fileInput2, "%s", padrao);

    if(x != EOF) return 1;
    else return 0;        
}

void close_file(){
    fclose(fileInput1);
    fclose(fileInput2);
    fclose(fileOutput);
}

/*void output(int habilidade){
    fprintf(fileOutput, "%d ", habilidade);
}*/