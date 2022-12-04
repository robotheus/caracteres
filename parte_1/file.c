#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>
#include "file.h"

FILE *fileInput1, *fileInput2, *fileOutput;

void open_file(char argv1[], char argv2[], int escolha){
    fileInput1 = fopen(argv1, "r");
    fileInput2 = fopen(argv2, "r");
    if(escolha == 1) fileOutput = fopen("dinamica.out", "w");
    else if(escolha == 2) fileOutput = fopen("shiftand.out", "w");
    else printf("ESCOLHA INCORRETA.\n");

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

int read_file_text2(char *texto, int *posicao, int *inicio){
    int y;
    strcpy(texto, "\0");
    (*posicao)++; //referente ao espaço

    y = fscanf(fileInput1, "%s", texto);
    for(int i = 0; i < strlen(texto); i++){
        //printf("%d %c\n", texto[i], texto[i]);
    }
    *inicio = *posicao;

    int caractere = 0;
    for (int j = 0; j < strlen(texto); j++) {
        caractere = texto[j];
        if (caractere < 0) {
            (*posicao)--;
            break;
        }
    }

    caractere = texto[strlen(texto) - 1];

    if(caractere >= 33 && caractere <= 47) {
        texto[strlen(texto) - 1] = 0;
        (*posicao)++; //referente ao ponto ou virgula
    }

    if(y != EOF) return 1;
    else {
        rewind(fileInput1);
        return 0;
    }
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

void output1(){
    fprintf(fileOutput, "\n");
}

void output2(char *s){
    fprintf(fileOutput, "%s  ", s);
}

void output3(long d){
    fprintf(fileOutput, "%ld  ", d);
}

double time_diff(struct timeval *start, struct timeval *end){
    return (end->tv_sec - start->tv_sec) + 1e-6*(end->tv_usec - start->tv_usec);
}