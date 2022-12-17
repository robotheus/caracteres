#define VAZIO           "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"
#define RETIRADO        "***********************************"

#define M 70000
#define N 100   //tamanho da chave
#define BASENUM 128  //base numerica que o algoritmo trabalha
#define MAXALFABETO 255 //constante usada em ExtraiProximaPalavra
#define MAXTAMVETORESDO  10
#define TRUE  1
#define FALSE 0
#define MAXTAMTEXTO     1000100
#define MAXTAMPADRAO    50
#define MAXCHAR         256

typedef char TipoTexto[MAXTAMTEXTO + 1];
typedef char TipoPadrao[MAXTAMPADRAO + 1];
typedef int TipoApontador;
typedef char TipoChave[N+1];
typedef int TipoPesos[N + 1];

typedef struct TipoItem {
  TipoChave Chave;
  int Freq, Ordem;
} TipoItem;

typedef int TipoIndice;
typedef TipoItem *TipoDicionario;
typedef short TipoAlfabeto[MAXALFABETO + 1];

typedef struct TipoBaseOffset {
  int Base, Offset;
} TipoBaseOffset;

typedef TipoBaseOffset* TipoVetoresBO;
typedef char TipoPalavra[256];
typedef TipoPalavra* TipoVetorPalavra;

void buscar(char *);
void comprime(char *, char *);
void bmh_c(TipoTexto, int, TipoPadrao, int, int *);
void Busca(FILE *, FILE *);
void GeraPesos(TipoPesos);
TipoIndice h(TipoChave, TipoPesos);
void Inicializa(TipoDicionario);
TipoApontador Pesquisa(TipoChave, TipoPesos, TipoDicionario);
void Insere(TipoItem *, TipoPesos, TipoDicionario);
void Retira(TipoChave , TipoPesos, TipoDicionario);
void DefineAlfabeto(TipoAlfabeto , FILE *);
void ExtraiProximaPalavra (TipoPalavra , int *, char *, FILE *, TipoAlfabeto);
char *Trim(char *);
void PrimeiraEtapa(FILE *, TipoAlfabeto, int *, TipoPalavra, char *, TipoDicionario, TipoPesos);
void CalculaCompCodigo(TipoDicionario, int);
void Particao(TipoIndice, TipoIndice, TipoIndice *, TipoIndice *, TipoDicionario);
void Ordena(TipoIndice, TipoIndice, TipoDicionario);
void QuickSort(TipoDicionario, TipoIndice *);
TipoIndice OrdenaPorFrequencia(TipoDicionario);
void GravaNumInt(FILE *, int);
int LeNumInt(FILE *);
int ConstroiVetores(TipoVetoresBO, TipoDicionario, int, FILE *);
int SegundaEtapa(TipoDicionario, TipoVetoresBO, TipoPesos, FILE *); 
void Escreve(FILE *, int *, int *);
int Codifica(TipoVetoresBO, int, int *, int);
void TerceiraEtapa(FILE *, TipoAlfabeto, int *, TipoPalavra, char *, TipoDicionario, TipoPesos, TipoVetoresBO, FILE *, int);
void Compressao(FILE *, FILE *, FILE *);
int LeVetores(FILE *, TipoBaseOffset *);
int LeVocabulario(FILE *, TipoVetorPalavra);
void Atribui(TipoPadrao, int , int c);