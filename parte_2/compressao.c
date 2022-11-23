#include <stdio.h>
#include <string.h>
#include <sys/time.h>
#include <stdlib.h>
#include "compressao.h"

void bmh_compressao(){
    FILE *ArqTxt = NULL;
    FILE *ArqAlf = NULL;
    FILE *ArqComprimido = NULL;

    TipoPalavra NomeArqTxt, NomeArqAlf, NomeArqComprimido, Opcao;

    printf("    (c) para Compressao\n");
    printf("    (p) para Pesquisa no texto comprimido\n");
    fgets(Opcao, MaxAlfabeto+1, stdin);

    strcpy(NomeArqAlf, "alfabeto.txt");
    ArqAlf = fopen(NomeArqAlf, "r");

    if(Opcao[0] == 'c'){
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
    char *Temp;

    for(int i = 0; i <= MaxAlfabeto; i++) Alfabeto[i] = FALSE;
    fgets(Simbolos, MaxAlfabeto + 1, ArqAlf);
    
    Temp = strchr(Simbolos, '\n');
    if(Temp != NULL) *Temp = 0;
    
    for(int i = 0; i <= strlen(Simbolos)-1; i++){
        Alfabeto[Simbolos[i]+127] = TRUE;
        Alfabeto[0] = FALSE;
    }
}

void GeraPesos(TipoPesos p){
    int i;

    struct timeval semente;
    gettimeofday(&semente, NULL);
    srand((int) (semente.tv_sec + 10000000*semente.tv_usec));

    for(i = 0; i < n; i++){
        p[i] = 1 + (int) (10000.0 * rand())/(RAND_MAX + 1.0);
    }
}

Indice h(TipoChave Chave, TipoPesos p){
    unsigned int Soma = 0;
    int comp = strlen(Chave);

    for(int i = 0; i< comp; i++) Soma += (unsigned int) Chave[i] * p[i];
    return (Soma % M);
}

void Inicializa(TipoDicionario T){
    for(int i = 0; i < M; i++) memcpy(T[i].Chave, Vazio, n);
}

Apontador Pesquisa(TipoChave Ch, TipoPesos p, TipoDicionario T){
    unsigned int i = 0;
    unsigned int Inicial;

    Inicial = h(Ch, p);

    while(strcmp(T[(Inicial + i) % M].Chave, Vazio) != 0 && strcmp(T[(Inicial + i) % M].Chave, Ch) != 0 && i < M) i++;

    if(strcmp(T[(Inicial + i) % M].Chave, Ch) == 0) return ((Inicial + i) % M);
    else return M;
}

void Insere(TipoItem x, TipoPesos p, TipoDicionario T){
    unsigned int i = 0;
    unsigned int Inicial;

    if(Pesquisa(x.Chave, p, T) < M){
        printf("Elemento ja esta presente\n");
        return;
    }

    Inicial = h(x.Chave, p);

    while(strcmp(T[(Inicial + i) % M].Chave, Vazio) != 0 && strcmp(T[(Inicial + i) % M].Chave, Retirado) != 0 && i < M) i++;

    if(i < M) strcpy(T[(Inicial + i) % M].Chave, x.Chave);
    else printf("Tabela cheia\n");
}

void Particao(Indice Esq, Indice Dir, Indice *i, Indice *j, Item *A){
    Item x, w;
    *i = Esq;
    *j = Dir;
    x = A[(*i + *j) / 2];

    do {
        while(x.Chave > A[*i].Chave) (*i)++;
        while(x.Chave < A[*j].Chave) (*j)--;

        if(*i <= *j){
            w = A[*i];
            A[*i] = A[*j];
            A[*j] = w;
            (*i)++;
            (*j)--;
        }
    } while (*i <= *j);
}

void Ordena(Indice Esq, Indice Dir, Item *A){
    Indice i, j;

    Particao(Esq, Dir, &i, &j, A);
    if(Esq < j) Ordena(Esq, j, A);
    if(i < Dir) Ordena(i, Dir, A);
}

void QuickSort(Item *A, Indice *x){
    Ordena(1, *x, A);
}


