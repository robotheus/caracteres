#include <stdio.h>
#include <string.h>
#include "dinamica.h"
#include "file.h"

void dinamica(char *texto, char *padrao, int erros, int *posicao){
    *posicao = 1;
    int x = 0;

    while(read_file_text2(texto)){
        
        if(x < 1) {
            printf("%s", padrao);
            x++;
        }
        //printf("texto: %s\n", texto);
            
        int x;
        x = levenshtein(texto, padrao);

        if(x <= erros) {
            printf("%3d", *posicao);
        }
        *posicao += strlen(texto);
    }
    printf("\n");
}

int min(int a, int b, int c){	
	if(a <= b && a <= c) return a;
	else if(b <= a && b <= c) return b;
	else if(c <= a && c <= b) return c;
}

int levenshtein(char *s1, char *s2){
    unsigned int x, y, s1len, s2len;
    
    s1len = strlen(s1);
    s2len = strlen(s2);
    
    unsigned int matrix[s2len+1][s1len+1];
    matrix[0][0] = 0;
    
    for (x = 1; x <= s2len; x++) matrix[x][0] = matrix[x-1][0] + 1;
    for (y = 1; y <= s1len; y++) matrix[0][y] = matrix[0][y-1] + 1;
    for (x = 1; x <= s2len; x++){
        for (y = 1; y <= s1len; y++)
            matrix[x][y] = min(matrix[x-1][y] + 1, matrix[x][y-1] + 1, matrix[x-1][y-1] + (s1[y-1] == s2[x-1] ? 0 : 1));
    }
    
    return(matrix[s2len][s1len]);
}