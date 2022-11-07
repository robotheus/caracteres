#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "file.h"

#define MAX_TEXTO 5000
#define MAX_PALAVRA 50
#define MAX_PADRAO 50

void main(int argc, char *argv[]){
    open_file(argv[2], argv[3]);

    int escolha = atoi(argv[1]);
    char *palavra = malloc(MAX_PALAVRA * sizeof(char)); //Maior palavra do texto: 30 caracteres
    char *texto = (char*) malloc(MAX_TEXTO * sizeof(char)); //Texto maximo suportado: 2250 caracteres
    char *padrao = malloc(MAX_PADRAO * sizeof(char)); //Maior padrao a ser buscado: 30 caracteres

    read_file_text(palavra, texto);
    
    while (read_file_pattern(padrao, MAX_PADRAO)) {
        for(int i = 2; i < strlen(padrao); i++) printf("%c", padrao[i-2]);
        printf("\n");
        switch (escolha){
            case 1:
                break;
            
            case 2:
                break;
                
            default:
                break;
        }
    }
    
    

    close_file();
    free(palavra);
    free(texto);
    free(padrao);
}