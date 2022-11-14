#include <stdio.h>
#include <string.h> 
#include "shiftand.h"

void ShiftAndAproximado(char *texto, long n, char *padrao, long m, long k) {
    printf("%s", padrao);

    long Masc[256], i, j, Ri, Rant, Rnovo;
    long R[11];
    long cont = 0, anterior = -1;
    long inicio, fim;

    for(i = 0; i < 256; i++) Masc[i] = 0;
    for(i = 1; i <= m; i++) {Masc[padrao[i - 1] + 127] |= 1 << (m - i);}

    R[0] = 0;
    Ri = 1 << (m - 1);

    for(j = 1; j <= k; j++) R[j] = (1 << (m - j)) | R[j - 1];

    for(i = 0; i < n; i++) {
        Rant = R[0];
        Rnovo = ((((unsigned long)Rant) >> 1) | Ri) & Masc[texto[i] + 127];
        R[0] = Rnovo;

        for(j = 1; j <= k; j++) {
            Rnovo = ((((unsigned long)R[j]) >> 1) & Masc[texto[i] + 127]) | Rant | (((unsigned long)(Rant | Rnovo)) >> 1);
            Rant = R[j];
            R[j] = Rnovo | Ri;
        }

        if((Rnovo & 1) != 0) {
            cont++;
            fim = i + 1;
            inicio = fim - strlen(padrao);
        } else cont = 0;

        if (cont != 0) {
            printf("%3ld", inicio + 2);
        }
    }
    printf("\n");
}
