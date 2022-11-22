#include <stdio.h>
#include <string.h>

#define BaseNum 128
#define MaxAlfabeto 255
#define MaxTamVetoresBO 10
#define TRUE 1
#define FALSE 0

typedef short TipoAlfabeto[MaxAlfabeto + 1];

typedef struct TipoBaseOfSet{
    int Base, Offset;
} TipoBaseOfSet;

typedef TipoBaseOfSet TipoVetoersBO[MaxTamVetoresBO + 1];
typedef char TipoPalavra[256];
typedef TipoPalavra TipoVetorPalavra[M + 1];

int main(int argc, char *argv[]){
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

    return 0;
}

void Compressao(FILE *ArqTxt, FILE *ArqAlf, FILE *ArqComprimido){
    TipoAlfabeto Alfabeto;
    TipoPalavra Palavra, Linha;
    int Ind = 1;
    int MaxCompCod;

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

DefineAlfabeto();