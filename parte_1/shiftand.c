void ShiftAndAproximado(char *texto, long n, char *padrao, long m, long k)
{ long Masc[MAXCHAR], i, j, Ri, Rant, Rnovo;
  long R[NUMMAXERROS + 1];
  for (i = 0; i < MAXCHAR; i++) Masc[i] = 0;
  for (i = 1; i <= m; i++) 
  { Masc[P[i-1] + 127] |= 1 << (m - i); }
  R[0] = 0;
  Ri = 1 << (m - 1);
  for (j = 1; j <= k; j++) R[j] = (1 << (m - j)) | R[j-1];
  for (i = 0; i < n; i++) 
    { Rant = R[0];
      Rnovo = ((((unsigned long)Rant) >> 1) | Ri) & Masc[T[i] + 127];
      R[0] = Rnovo;
      for (j = 1; j <= k; j++) 
        { Rnovo = ((((unsigned long)R[j]) >> 1) & Masc[T[i] + 127]) 
                  | Rant | (((unsigned long)(Rant | Rnovo)) >> 1);
          Rant = R[j];
          R[j] = Rnovo | Ri;
        }
      if ((Rnovo & 1) != 0)
      printf(" Casamento na posicao %12ld\n", i + 1);
    }
}