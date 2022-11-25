#include <stdio.h>
#include <string.h>
#include <sys/time.h>
#include <stdlib.h>
#include <publib.h>
#include "compressao.h"
#include "bmh.h"

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

                if(strcmp(Trim(Palavra), "") && /*here->*/(*Trim(Palavra)) != (char)0){
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

                
                if(strcmp(Trim(Palavra), "") && /*here->*/(*Trim(Palavra)) != (char)0){
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

int Codifica(TipoVetoresBO VetoresBaseOffSet, int Ordem, int *c, int MaxCompCod){
    *c = 1;

    while(Ordem >= VetoresBaseOffSet[*c + 1].Offset && *c + 1<= MaxCompCod) (*c)++;

    return (Ordem - VetoresBaseOffSet[*c].Offset + VetoresBaseOffSet[*c].Base);
}

int ConstroiVetores(TipoVetoresBO VetoresBaseOffset, TipoDicionario Vocabulario, int x, FILE *ArqComprimido){
    int Wcs[MaxTamVetoresBO + 1];
    int i, MaxCompCod;
    MaxCompCod = Vocabulario[x].Freq;

    for(i = 1; i <= x; i++){
        Wcs[Vocabulario[i].Freq]++;
        VetoresBaseOffset[Vocabulario[i].Freq].Offset = i - Wcs[Vocabulario[i].Freq] + 1;
    }

    VetoresBaseOffset[1].Base = 0;

    for(i = 2; i <= MaxCompCod; i++){
        VetoresBaseOffset[i].Base = BaseNum * (VetoresBaseOffset[i - 1].Base + Wcs[i - 1]);
        if(VetoresBaseOffset[i].Offset == 0) VetoresBaseOffset[i].Offset = VetoresBaseOffset[i - 1].Offset;
    }

    GravaNumInt(ArqComprimido, MaxCompCod);
    for(i = 1; i <= MaxCompCod; i++){
        GravaNumInt(ArqComprimido, VetoresBaseOffset[i].Base);
        GravaNumInt(ArqComprimido, VetoresBaseOffset[i].Offset);
    }

    return MaxCompCod;
}

int LeNumInt(FILE *ArqComprimido){
    int Num;
    fread(&Num, sizeof(int), 1, ArqComprimido);
    return Num;
}

void GravaNumInt(FILE *ArqComprimido, int Num){
    fwrite(&Num, sizeof(int), 1, ArqComprimido);
}

Indice OrdenaPorFrequencia(TipoDicionario Vocabulario){
    Indice i;
    Indice x = 1;
    TipoItem Item;

    Item = Vocabulario[1];

    for(i = 0; i <= M - 1; i++){
        if(strcmp(Vocabulario[i].Chave, Vazio)){
            if(i != 1) {
                Vocabulario[x] = Vocabulario[i];
                x++;
            }
        }
    }

    if(strcmp(Item.Chave, Vazio)) Vocabulario[x] = Item;
    else x--;

    QuickSort(Vocabulario, &x);
    return x;
}

void Escreve(FILE *ArqComprimido, int *Codigo, int *c){
    unsigned char Saida[MaxTamVetoresBO + 1];
    int i = 1, cTmp;
    cTmp = *c;
    
    Saida[i] = ((unsigned)(*Codigo)) >> ((*c - 1) * 8 - *c + 1) | 0x80;
    i++;
    (*c)--;

    while(*c > 0){
        Saida[i] = ((unsigned)(*Codigo)) >> ((*c - 1) * 8 - *c + 1);
        i++;
        (*c)--;
    }

    for(i = 1; i <= cTmp; i++) fwrite(&Saida[i], sizeof(unsigned char), 1, ArqComprimido);
}

int LeVetores(FILE *ArqComprimido, TipoBaseOfSet *VetoresBaseOffset){
    int MaxCompCod, i;
    MaxCompCod = LeNumInt(ArqComprimido);

    for(i = 1; i <= MaxCompCod; i++){
        VetoresBaseOffset[i].Base = LeNumInt(ArqComprimido);
        VetoresBaseOffset[i].Offset = LeNumInt(ArqComprimido);
    }

    return MaxCompCod;
}

void ExtraiProximaPalavra(TipoPalavra Result, int *Indice, char *Linha, FILE *ArqTxt, TipoAlfabeto Alfabeto){
    short FimPalavra = FALSE, Aux = FALSE;
    Result[0] = '\0';

    if(*Indice > strlen(Linha)){
        if(fgets(Linha, MaxAlfabeto + 1, ArqTxt)){
            sprintf(Linha + strlen(Linha), " %c", (char)0);
            *Indice = 1;
        } else{
            sprintf(Linha, " %c", (char)0);
            FimPalavra = TRUE;
        }
    }

    while(*Indice <= strlen(Linha) && !FimPalavra){
        if(Alfabeto[Linha[*Indice - 1] + 127]){
            sprintf(Result + strlen(Result), " %c", Linha[*Indice - 1]);
            Aux = TRUE;
        } else {
            if(Aux){
                if(Linha[*Indice - 1] != (char)0) (*Indice)--;
            } else {
                sprintf(Result + strlen(Result), " %c", Linha[*Indice - 1]);
            }

            FimPalavra = TRUE;
        }
        (*Indice)++;
    }
}

void Busca(FILE *ArqComprimido, FILE *ArqAlf){
    TipoAlfabeto Alfabeto;
    int Ind, Codigo, MaxCompCod;
    TipoVetorPalavra Vocabulario;
    TipoVetoresBO VetoresBaseOffset;
    TipoPalavra p;

    int c, Ord, NumNodosFolhas;
    TipoTexto T;
    TipoPadrao Padrao;
    int x = 1;

    DefineAlfabeto(Alfabeto, ArqAlf);
    MaxCompCod = LeVetores(ArqComprimido, VetoresBaseOffset);
    NumNodosFolhas = LeVocabulario(ArqComprimido, Vocabulario);

    while(fread(&T[x], sizeof(char), 1, ArqComprimido)) x++;

    do {
        printf("Padrao: ");
        fgets(p, MaxAlfabeto + 1, stdin);
        p[strlen(p) - 1] = '\0';

        for(Ind = 1; Ind <= NumNodosFolhas; Ind++){
            if(!strcmp(Vocabulario[Ind], p)) Ord = Ind;
        }

        Codigo = Codifica(VetoresBaseOffset, Ord, &c, MaxCompCod);
        Atribui(Padrao, Codigo, c);
        BMH(T, x, Padrao, c);
    } while (strcmp(p, "s"));
}

void Atribui(TipoPadrao P, int Codigo, int c){
    int i = 1, cTmp = c;
    P[i] = (char)((Codigo >> ((c-1) * 8 - c + 1)) | 0x80);
    i++;
    c--;

    while(c > 0){
        P[i] = (char)(Codigo >> ((c-1) * 8 - c + 1));
        i++;
        c--;
    }
}

int LeVocabulario(FILE *ArqComprimido, TipoVetorPalavra Vocabulario){
    int NumNodosFolhas, i;
    TipoPalavra Palavra;

    char Ch;
    NumNodosFolhas = LeNumInt(ArqComprimido);

    for(i = 1; i <= NumNodosFolhas; i++){
        *Palavra = '\0';

        do{
            fread(&Ch, sizeof(unsigned char), 1, ArqComprimido);

            if(Ch != (char)0) sprintf(Palavra + strlen(Palavra), " %c", Ch);
        } while (Ch != (char)0);

        strcpy(Vocabulario[i], Palavra);
    }
    return NumNodosFolhas;
}