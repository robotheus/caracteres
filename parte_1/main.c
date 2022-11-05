#include <stdio.h>
#include <stdlib.h>
#include "file.h"

#define MAX_TEXTO 2500
#define MAX_PALAVRA_CHAVE 30

void main(int argc, char *argv[]){
    open_file(argv[2], argv[3], argv[5]);

    int escolha = argv[1];
    char *palavra_chave = (char) malloc(MAX_PALAVRA_CHAVE * sizeof(char)); //Maior palavra chave: 30 caracteres
    char *texto = (char*) malloc(MAX_TEXTO * sizeof(char)); //Texto maximo suportado: 2250 caracteres

    switch (escolha){
        case 1:
            //programacao dinamica
            break;
        
        case 2:
            //shift and aproximado
            break;
            
        default:
            break;
    }
}