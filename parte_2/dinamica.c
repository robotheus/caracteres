#include <stdio.h>
#include <string.h>
#include "dinamica.h"
#include "file.h"

void dinamica(char *texto, char *padrao, int erros, int *posicao, int *inicio, int *comparacoes){
    int x = 0;
    while(read_file_text2(texto, posicao, inicio)){
        if(x < 1) {
            output2(padrao);
            x++;
        }
            
        int y;
        y = levenshtein(texto, padrao, comparacoes);

        if(y <= erros) {
            output3(*inicio);
        }

        (*posicao) += strlen(texto);
    }
    output1();
}

int min(int a, int b, int c){	
	if(a <= b && a <= c) return a;
	else if(b <= a && b <= c) return b;
	else if(c <= a && c <= b) return c;
}

int levenshtein(char *s1, char *s2, int *comparacoes){
    unsigned int x, y, s1len, s2len;
    
    s1len = strlen(s1);
    s2len = strlen(s2);
    
    unsigned int matriz[s2len+1][s1len+1];
    matriz[0][0] = 0;
    
    for (x = 1; x <= s2len; x++) matriz[x][0] = matriz[x-1][0] + 1;
    for (y = 1; y <= s1len; y++) matriz[0][y] = matriz[0][y-1] + 1;
    for (x = 1; x <= s2len; x++){
        for (y = 1; y <= s1len; y++)
            (*comparacoes)++;
            matriz[x][y] = min(matriz[x-1][y] + 1, matriz[x][y-1] + 1, matriz[x-1][y-1] + (s1[y-1] == s2[x-1] ? 0 : 1));
    }
    
    return(matriz[s2len][s1len]);
}