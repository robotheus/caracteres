#define BaseNum 128
#define MaxAlfabeto 255
#define MaxTamVetoresBO 10
#define TRUE 1
#define FALSE 0
#define MaxTamTexto 1000
#define MaxTamPadrao 10
#define Maxchar 256
#define NumMaxErros 10
#define n 11
#define M 7
#define Vazio "!!!!!!!!!!"
#define Retirado "**********"

typedef unsigned int Apontador;
typedef unsigned int TipoFreq;
typedef unsigned int TipoOrdem;
typedef unsigned char TipoChave[n];
typedef unsigned TipoPesos[n];
typedef unsigned int Indice;

typedef struct TipoItem{
    TipoChave Chave;
    TipoFreq Freq;
    TipoOrdem Ordem;
} TipoItem;

typedef TipoItem TipoDicionario[M];
typedef char TipoTexto[MaxTamTexto];
typedef char TipoPadrao[MaxTamPadrao];
typedef short TipoAlfabeto[MaxAlfabeto + 1];

typedef struct TipoBaseOfSet{
    int Base, Offset;
} TipoBaseOfSet;

typedef TipoBaseOfSet TipoVetoresBO[MaxTamVetoresBO + 1];
typedef char TipoPalavra[256];
typedef TipoPalavra TipoVetorPalavra[M + 1];
typedef unsigned char TipoChave[n];
typedef int ChaveTipo;

typedef struct Item{
    ChaveTipo Chave;
} Item;

void bmh_compressao();
void Compressao(FILE *, FILE *, FILE *);
void DefineAlfabeto(TipoAlfabeto, FILE *);
void GeraPesos(TipoPesos);
Indice h(TipoChave, TipoPesos);
void Inicializa(TipoDicionario);
Apontador Pesquisa(TipoChave, TipoPesos, TipoDicionario);
void Insere(TipoItem, TipoPesos, TipoDicionario);
void Particao(Indice, Indice, Indice *, Indice *, Item *);
void Ordena(Indice, Indice, Item *);
void QuickSort(Item *, Indice *);
void PrimeiraEtapa(FILE *, TipoAlfabeto, int *, TipoPalavra, char *, TipoDicionario, TipoPesos);
int SegundaEtapa(TipoDicionario, TipoVetoresBO, TipoPesos, FILE *);
void TerceiraEtapa(FILE *, TipoAlfabeto , int *, TipoPalavra, char *, TipoDicionario, TipoPesos, TipoVetoresBO, FILE *, int);
void CalculaCompCodigo(TipoDicionario, int);
int Codifica(TipoVetoresBO, int, int *, int);
int ConstroiVetores(TipoVetoresBO, TipoDicionario, int, FILE *);
int LeNumInt(FILE *);
void GravaNumInt(FILE *, int);
Indice OrdenaPorFrequencia(TipoDicionario);
void Escreve(FILE *, int *, int *);
int LeVetores(FILE *, TipoBaseOfSet *);
void ExtraiProximaPalavra(TipoPalavra, int *, char *, FILE *, TipoAlfabeto);
void Busca(FILE *, FILE *ArqAlf);
void Atribui(TipoPadrao, int, int);
int LeVocabulario(FILE *, TipoVetorPalavra);