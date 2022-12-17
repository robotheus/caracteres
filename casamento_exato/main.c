#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>
#include "file.h"
#include "bmh.h"
#include "compressao.h"

#define MAX_TEXTO 5000000
#define MAX_PALAVRA 100
#define MAX_PADRAO 100


void main(int argc, char *argv[]){ 
    int escolha = atoi(argv[1]);    
    open_file(argv[2], argv[3], escolha);
    

    if(escolha == 1) {
        char *palavra = malloc(MAX_PALAVRA * sizeof(char)); 
        char *texto = malloc(MAX_TEXTO * sizeof(char)); 
        char *padrao = malloc(MAX_PADRAO * sizeof(char));
        int *comparacoes = malloc(sizeof(int));
        *comparacoes = 0;

        read_file_text(palavra, texto);
        
        struct timeval start, end;
        double time = 0.0;
        
        while(read_file_pattern(padrao)){    
            gettimeofday(&start, NULL);
            BMH(texto, strlen(texto), padrao, strlen(padrao), comparacoes);
            gettimeofday(&end, NULL);
            time += time_diff(&start, &end);
        }

        printf("Tempo BMH em arquivo nao comprimido: %.10lf sec.\n", time);
        printf("Comparacoes BMH em arquivo nao comprimido: %d\n", *comparacoes);
        free(comparacoes);
        comparacoes = NULL;
        free(palavra);
        free(texto);
        free(padrao);
    } else if (escolha == 2){
        struct timeval start, end;
        double time = 0.0;

        gettimeofday(&start, NULL);
        comprime(argv[2], argv[4]);
        gettimeofday(&end, NULL);
        time += time_diff(&start, &end);
        printf("Tempo de compressao do arquivo: %.10lf sec.\n", time);
        buscar(argv[4]);
    }
    
    close_file();
}