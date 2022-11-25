#include <stdio.h>
#include "bmh.h"

void BMH(char *texto, long n, char *padrao, long m){ 
    long i, j, k, d[256 + 1];
    
    for (j = 0; j <= 256; j++) d[j] = m;
    for (j = 1; j < m; j++) d[padrao[j-1]] = m - j;
    i = m;
    
    printf("%s", padrao);
    while (i <= n){ 
        k = i;
        j = m;
        
        while (texto[k-1] == padrao[j-1] && j > 0) { 
            k--; j--; 
        }

        if (j == 0) printf("%3ld", k + 1);
        
        i += d[texto[i-1]];
    }

    printf("\n");
}