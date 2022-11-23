#define BaseNum 128
#define MaxAlfabeto 255
#define MaxTamVetoresBO 10
#define TRUE 1
#define FALSE 0
#define MaxTamTexto 1000
#define MaxTamPadrao 10
#define n 11
#define M 7
#define Vazio "!!!!!!!!!!"
#define Retirado "**********"

typedef unsigned int Apontador;
typedef unsigned char TipoChave[n];
typedef unsigned TipoPesos[n];
typedef unsigned int Indice;

typedef struct TipoItem{
    TipoChave Chave;
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

void bmh_compressao();
void Compressao(FILE *, FILE *, FILE *);
void DefineAlfabeto(TipoAlfabeto, FILE *);