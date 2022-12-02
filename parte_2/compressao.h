#define VAZIO           "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"
#define RETIRADO        "***********************************"

#define M 67001
#define N 35   /* Tamanho da chave */
#define BASENUM 128  /* Base numerica que o algoritmo trabalha */
#define MAXALFABETO 255 /* Constante usada em ExtraiProximaPalavra */
#define MAXTAMVETORESDO  10
#define TRUE  1
#define FALSE 0
#define MAXTAMTEXTO     100000
#define MAXTAMPADRAO    10
#define MAXCHAR         256

typedef char TipoTexto[MAXTAMTEXTO + 1];
typedef char TipoPadrao[MAXTAMPADRAO + 1];
typedef int TipoApontador;
typedef char TipoChave[N+1];
typedef int TipoPesos[N + 1];
typedef struct TipoItem {
  TipoChave Chave;
  /* outros componentes */
  int Freq, Ordem;
} TipoItem;
typedef int TipoIndice;
//typedef TipoItem TipoDicionario[M + 1];
typedef TipoItem* TipoDicionario;
typedef short TipoAlfabeto[MAXALFABETO + 1];
typedef struct TipoBaseOffset {
  int Base, Offset;
} TipoBaseOffset;
typedef TipoBaseOffset* TipoVetoresBO;
typedef char TipoPalavra[256];
typedef TipoPalavra* TipoVetorPalavra;
//typedef TipoBaseOffset TipoVetoresBO[MAXTAMVETORESDO + 1];
//typedef TipoPalavra TipoVetorPalavra[M + 1];


int bmh_compressao();