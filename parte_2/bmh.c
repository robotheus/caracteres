#include <stdio.h>
#include "bmh.h"
#include "file.h"
#include <stdlib.h>

void BMH(char *texto, long n, char *padrao, long m){ 
    long i, j, k, d[256 + 1];
    //calcula os deslocamentos
    for (j = 0; j <= 256; j++) d[j] = m;
    for (j = 1; j < m; j++) d[padrao[j-1]] = m - j;
    i = m;
    
    //realiza as comparacoes e desloca
    output2(padrao);
    while (i <= n){ 
        k = i;
        j = m;
        
        while (texto[k-1] == padrao[j-1] && j > 0) { 
            k--; j--;
        }

        if(j == 0) output3(k + 1);
        
        if(d[texto[i-1]] > m || d[texto[i-1]] <= 0){
            //precaução caso algum caractere inválido, que consequentemente nao é uma das letras do padrao, receba um valor nao previsto
            d[texto[i-1]] = m;
        }
        i += d[texto[i-1]];
    }

    output1();
    
}