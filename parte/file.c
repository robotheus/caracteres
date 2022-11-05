#include <stdio.h>
#include <string.h>
#include "file.h"

FILE *fileInput1, *fileInput2, *fileOutput;

void open_file(char argv1[], char argv2[], char argv3[]){
    fileInput1 = fopen(argv1, "r");
    fileInput2 = fopen(argv2, "r");
    fileOutput = fopen(argv3, "w");

    if(fileInput1 == NULL || fileInput2 == NULL) printf("ERRO AO ABRIR O ARQUIVO.\n");
}

int read_file(){
    
}

void close_file(){
    fclose(fileInput1);
    fclose(fileInput2);
    fclose(fileOutput);
}

void output1(int habilidade){
    fprintf(fileOutput, "%d ", habilidade);
}

void output2(int vertice, int selecionados){
    fprintf(fileOutput, "%d %d ", vertice, selecionados);
}

void output3(){
    fprintf(fileOutput, "\n");
}