#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "file.h"
#include "bmh.h"
#include "compressao.h"

#define MAX_TEXTO 5000
#define MAX_PALAVRA 50
#define MAX_PADRAO 50

void main(int argc, char *argv[]){ 
    open_file(argv[2], argv[3]);

    int escolha = atoi(argv[1]);
    char *palavra = malloc(MAX_PALAVRA * sizeof(char)); 
    char *texto = malloc(MAX_TEXTO * sizeof(char)); 
    char *padrao = malloc(MAX_PADRAO * sizeof(char));
    
    if(escolha == 1) {
        read_file_text(palavra, texto);
        
        while(read_file_pattern(padrao)){
            BMH(texto, strlen(texto), padrao, strlen(padrao));
        }

        free(palavra);
        free(texto);
        free(padrao);
    } else if (escolha == 2){
        bmh_compressao(argv[2], argv[3], argv[4]);
    }
    
    close_file();
}