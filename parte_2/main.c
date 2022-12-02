#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "file.h"
#include "bmh.h"
#include "compressao.h"

#define MAX_TEXTO 5000
#define MAX_PALAVRA 50
#define MAX_PADRAO 50

void main(int argc, char *argv[]){ //./tp3 2 texto.txt padrao.txt
    open_file(argv[2], argv[3]);

    int escolha = atoi(argv[1]);
    char *palavra = malloc(MAX_PALAVRA * sizeof(char)); //Maior palavra do texto: 30 caracteres
    char *texto = malloc(MAX_TEXTO * sizeof(char)); //Texto maximo suportado: 2250 caracteres
    char *padrao = malloc(MAX_PADRAO * sizeof(char)); //Maior padrao a ser buscado: 30 caracteres

    if (escolha == 1) read_file_text(palavra, texto);
    
    while(read_file_pattern(padrao)){
        if(escolha == 1){
            BMH(texto, strlen(texto), padrao, strlen(padrao));
        } else if (escolha == 2){
            bmh_compressao(padrao);
        }
    }
    
    close_file();
    free(palavra);
    free(texto);
    free(padrao);
}