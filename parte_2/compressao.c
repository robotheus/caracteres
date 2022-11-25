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

void PrimeiraEtapa(FILE *ArqTxt, TipoAlfabeto Alfabeto, int *Indice, TipoPalavra Palavra, char *Linha, TipoDicionario Vocabulario, TipoPesos p){
    TipoItem Elemento;
    int i;
    do {
        ExtraiProximaPalavra(Palavra, Indice, Linha, ArqTxt, Alfabeto);
        memcpy(Elemento.Chave, Palavra, sizeof(TipoChave));
        Elemento.Freq = 1;
        if(*Palavra != '\0'){
            i = Pesquisa(Elemento.Chave, p, Vocabulario);
            if(i < M) Vocabulario[i].Freq++;
            else Insere(Elemento, p, Vocabulario);

            do {
                ExtraiProximaPalavra(Palavra, Indice, Linha, ArqTxt, Alfabeto);
                memcpy(Elemento.Chave, Palavra, sizeof(TipoChave));

                if(strcmp(Trim(Palavra), "") && (*Trim(Palavra)) != (char)0){
                    i = Pesquisa(Elemento.Chave, p, Vocabulario);
                    if(i < M) Vocabulario[i].Freq;
                    else Insere(Elemento, p, Vocabulario);
                }
            } while(strcmp(Palavra, ""));
        }
    } while (Palavra[0] != '\0');
}

int SegundaEtapa(TipoDicionario Vocabulario, TipoVetoresBO VetoresBaseOffset, TipoPesos p, FILE *ArqComprimido){
    int Result, i, j, NumNodosFolhas, PosArq;
    TipoItem Elemento;
    char Ch;
    TipoPalavra Palavra;
    NumNodosFolhas = OrdenaPorFrequencia(Vocabulario);
    CalculaCompCodigo(Vocabulario, NumNodosFolhas);
    Result = ConstroiVetores(VetoresBaseOffset, Vocabulario, NumNodosFolhas, ArqComprimido);

    GravaNumInt(ArqComprimido, NumNodosFolhas);
    PosArq = ftell(ArqComprimido);

    for(i = 1; i <= NumNodosFolhas; i++){
        j = 1;

        while(Vocabulario[i].Chave[j-1] != (char)0){
            fwrite(&Vocabulario[i].Chave[j-1], sizeof(char), 1, ArqComprimido);
            j++;
        }

        Ch = (char)0;
        fwrite(&Ch, sizeof(char), 1, ArqComprimido);
    }

    fseek(ArqComprimido, PosArq, SEEK_SET);
    Inicializa(Vocabulario);

    for(i = 1; i <= NumNodosFolhas; i++){
        *Palavra = '\0';
        do {
            fread(&Ch, sizeof(char), 1, ArqComprimido);
            if(Ch != (char)0) sprintf(Palavra + strlen(Palavra), " %c", Ch);
        } while(Ch != (char)0);

        memcpy(Elemento.Chave, Palavra, sizeof(TipoChave));
        Elemento.Ordem = i;
        j = Pesquisa(Elemento.Chave, p, Vocabulario);

        if(j >= M) Insere(Elemento, p, Vocabulario);
    }

    return Result;
}

void TerceiraEtapa(FILE *ArqTxt, TipoAlfabeto Alfabeto, int *Indice, TipoPalavra Palavra, char *Linha, TipoDicionario Vocabulario, TipoPesos p, TipoVetoresBO VetoresBaseOffset, FILE *ArqComprimido, int MaxCompCod) {
    Apontador Pos;
    TipoChave Chave;
    int Codigo, c;

    do{
        ExtraiProximaPalavra(Palavra, Indice, Linha, ArqTxt, Alfabeto);
        memcpy(Chave, Palavra, sizeof(TipoChave));
        if(*Palavra != '\0'){
            Pos = Pesquisa(Chave, p,  Vocabulario);
            Codigo = Codifica(VetoresBaseOffset, Vocabulario[Pos].Ordem, &c, MaxCompCod);
            Escreve(ArqComprimido, &Codigo, &c);

            do {
                ExtraiProximaPalavra(Palavra, Indice, Linha, ArqTxt, Alfabeto);

                if(strcmp(Trim(Palavra), "") && (*Trim(Palavra)) != (char)0){
                    memcpy(Chave, Palavra, sizeof(TipoChave));
                    Pos = Pesquisa(Chave, p, Vocabulario);
                    Codigo = Codifica(VetoresBaseOffset, Vocabulario[Pos].Ordem, &c, MaxCompCod);
                    Escreve(ArqComprimido, &Codigo, &c);
                }
            } while (strcmp(Palavra, ""));
        }
    } while (*Palavra != '\0');
}

void CalculaCompCodigo(TipoDicionario A, int y){
    int u = 0, h = 0, NoInt, Prox, Raiz, Folha, Disp = 1, x, Resto;

    if(y > BaseNum - 1) Resto = 1 + ((y - BaseNum) % (BaseNum - 1));
    else Resto = y - 1;

    NoInt = 1 + ((n - Resto) / (BaseNum - 1));

    if(Resto < 2) Resto = BaseNum;
    for(x = y - 1; x >= (n - Resto) + 1; x--) A[n].Freq += A[x].Freq;

    Raiz = n;
    Folha = n - Resto;

    for(Prox = n - 1; Prox >= (n - NoInt) + 1; Prox--){
        if(Folha < 1 || Raiz > Prox && A[Raiz].Freq <= A[Folha].Freq){
            A[Prox].Freq = A[Raiz].Freq; 
            A[Raiz].Freq = Prox;
            Raiz--;
        } else{
            A[Prox].Freq = A[Folha].Freq;
            Folha--;
        }

        for(x = 1; x <= BaseNum - 1; x++){
            if(Folha < 1 || Raiz > Prox && A[Raiz].Freq <= A[Folha].Freq){
                A[Prox].Freq += A[Raiz].Freq;
                A[Raiz].Freq = Prox;
                Raiz--;
            } else {
                A[Prox].Freq += A[Folha].Freq;
                Folha--;
            }
        }
    }

    A[Prox + 1].Freq = 0; Raiz = Prox + 1;
    for(Prox = Raiz + 1; Prox <= y; Prox++) A[Prox].Freq = A[A[Prox].Freq].Freq + 1;

    Prox = 1;

    while (Disp > 0){
        while(Raiz <= y && A[Raiz].Freq == h) {
            u++;
            Raiz++;
        }

        while(Disp > u) {
            A[Prox].Freq = h;
            Prox++;
            Disp--;

            if(Prox > y){
                u = 0;
                break;
            }
        }

        Disp = BaseNum * u;
        h++;
        u = 0;
    }
    
}