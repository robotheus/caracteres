#include <stdio.h>
#include <string.h>
#include "bmh_compressao.h"

void bmh_compressao(){
    FILE *Ar1Txt = NULL;
    FILE *ArqAlf = NULL;
    FILE *ArqComprimido = NULL;

    TipoPalavra NomeArqTxt, NomeArqAlf, NomeArqComprimido, Opcao;

    printf("    (c) para Compressao\n");
    printf("    (p) para Pesquisa no texto comprimido\n");
    fgets(Opcao, MaxAlfabeto+1, stdin);

    strcpy(NomeArqAlf, "alfabeto.txt");
    ArqAlf = fopen(NomeArqAlf, r);

    if(Opcao == 'c'){
        printf("Arquivo a ser comprimido: ");
        fgets(NomeArqTxt, MaxAlfabeto+1, stdin);
        NomeArqTxt[strlen(NomeArqTxt)-1] = '\0';
        
        printf("Arquivo comprimido a ser gerado: ");
        fgets(NomeArqComprimido, MaxAlfabeto+1, stdin);
        NomeArqComprimido[strlen(NomeArqTxt)-1] = '\0';

        ArqTxt = fopen(NomeArqTxt, "r");
        ArqComprimido = fopen(NomeArqComprimido, "w+b");
        
        Compressao(ArqTxt, ArqAlf, ArqComprimido);

        fclose(ArqTxt);
        ArqTxt = NULL;
        fclose(ArqComprimido);
        ArqComprimido = NULL;

    } else if(Opcao[0] == 'p'){
        printf("Arquivo comprimido a ser pesquisado: ");
        fgets(NomeArqComprimido, MaxAlfabeto+1, stdin);
        NomeArqComprimido[strlen(NomeArqComprimido)-1] = '\0';
        strcpy(NomeArqComprimido, NomeArqComprimido);
        ArqComprimido = fopen(NomeArqComprimido, "r+b");
        
        Busca(ArqComprimido, ArqAlf);
        fclose(ArqComprimido);
        ArqComprimido = NULL;
    }
}

void Compressao(FILE *ArqTxt, FILE *ArqAlf, FILE *ArqComprimido){
    TipoAlfabeto Alfabeto;
    TipoPalavra Palavra, Linha;
    int Ind = 1;
    int MaxCompCod;

    TipoDicionario Vocabulario;
    TipoPesos p;
    TipoVetoresBO VetoresBaseOffset;

    DefineAlfabeto(Alfabeto, ArqAlf);
    *Linha = '\0';
    Inicializa(Vocabulario);
    GeraPesos(p);

    PrimeiraEtapa(ArqTxt, Alfabeto, &Ind, Palavra, Linha, Vocabulario, p);

    MaxCompCod = SegundaEtapa(Vocabulario, VetoresBaseOffset, p, ArqComprimido);
    fseek(ArqTxt, 0, SEEK_SET);
    Ind = 1;
    *Linha = '\0';

    TerceiraEtapa(ArqTxt, Alfabeto, &Ind, Palavra, Linha, Vocabulario, p, VetoresBaseOffset, ArqComprimido, MaxCompCod);
}

void DefineAlfabeto(TipoAlfabeto Alfabeto, FILE *ArqAlf){
    char Simbolos[MaxAlfabeto + 1];
    int i;
    char *Temp;

    for(int i = 0; i <= MaxAlfabeto; i++) Alfabeto[i] = FALSE;
    fgets(Simbolos, MaxAlfabeto + 1, ArqAlf);
    
    Temp = strchr(Simbolos, '\n');
    if(Temp != NULL) *Temp = 0;
    
    for(i = 0; i <= strlen(Simbolos)-1; i++){
        Alfabeto[Simbolos[i]+127] = TRUE;
        Alfabeto[0] = FALSE;
    }
}

void Inicializa(TipoDicionario T){
    for(int i = 0; i < M; i++) memcpy(T[i].Chave, Vazio, n);
}

