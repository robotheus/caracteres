#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>
#include "file.h"
#include "shiftand.h"
#include "dinamica.h"

#define MAX_TEXTO 5000000
#define MAX_PALAVRA 100
#define MAX_PADRAO 100

void main(int argc, char *argv[]){
    int escolha = atoi(argv[1]);
    int erros = atoi(argv[4]);
    int *comparacoes = malloc(sizeof(int));
    *comparacoes = 0;
    open_file(argv[2], argv[3], escolha);

    char *palavra = malloc(MAX_PALAVRA * sizeof(char)); //Maior palavra do texto: 50 caracteres
    char *texto = malloc(MAX_TEXTO * sizeof(char)); //Texto maximo suportado: 1000000 caracteres
    char *padrao = malloc(MAX_PADRAO * sizeof(char)); //Maior padrao a ser buscado: 50 caracteres

    struct timeval start, end;
    double time = 0.0;

    if (escolha == 2) read_file_text(palavra, texto);
    
    while(read_file_pattern(padrao)){
        if(escolha == 1){   
            int *posicao, *inicio;
            posicao = malloc(sizeof(int));
            inicio = malloc(sizeof(int));
            *posicao = 0; *inicio = 0;
            gettimeofday(&start, NULL);
            dinamica(texto, padrao, erros, posicao, inicio, comparacoes);
            gettimeofday(&end, NULL);
            time += time_diff(&start, &end);
            free(posicao);
            free(inicio);
        } else if (escolha == 2){
            gettimeofday(&start, NULL);
            ShiftAndAproximado(texto, strlen(texto), padrao, strlen(padrao), erros, comparacoes);
            gettimeofday(&end, NULL);
            time += time_diff(&start, &end);
        }
    }
    if(escolha == 1) {
        printf("Tempo somado programacao dinamica: %.10lf sec.\n", time);
        printf("Comparacoes somadas da programacao dinamica: %d\n", *comparacoes);
    }
    else if(escolha == 2) {
        printf("Tempo somado do shift-and: %.10lf sec.\n", time);
        printf("Comparacoes somadas do shift-and: %d\n", *comparacoes);
    }
        
    close_file();
    free(comparacoes);
    free(palavra);
    free(texto);
    free(padrao);
}