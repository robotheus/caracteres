#define VAZIO           "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"
#define RETIRADO        "***********************************"

#define M 70000
#define N 100   //Tamanho da chave
#define BASENUM 128  //base numerica que o algoritmo trabalha
#define MAXALFABETO 255 //Constante usada em ExtraiProximaPalavra
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

void buscar(char *comprimido);
void comprime(char *texto, char *comprimido);
void bmh_c(TipoTexto T, int n, TipoPadrao P, int m);
void Busca(FILE *ArqComprimido, FILE *ArqAlf);
void GeraPesos(TipoPesos p);
TipoIndice h(TipoChave Chave, TipoPesos p);
void Inicializa(TipoDicionario T);
TipoApontador Pesquisa(TipoChave Ch, TipoPesos p, TipoDicionario T);
void Insere(TipoItem * x, TipoPesos p, TipoDicionario T);
void Retira(TipoChave Ch, TipoPesos p, TipoDicionario T);
void DefineAlfabeto(TipoAlfabeto Alfabeto, FILE *ArqAlf);
void ExtraiProximaPalavra (TipoPalavra Result, int *TipoIndice, char *Linha, FILE *ArqTxt, TipoAlfabeto Alfabeto);
char *Trim(char *str);
void PrimeiraEtapa(FILE *ArqTxt, TipoAlfabeto Alfabeto, int *TipoIndice, TipoPalavra Palavra, char *Linha, TipoDicionario Vocabulario, TipoPesos p);
void CalculaCompCodigo(TipoDicionario A, int n);
void Particao(TipoIndice Esq, TipoIndice Dir, TipoIndice *i, TipoIndice *j, TipoDicionario A);
void Ordena(TipoIndice Esq, TipoIndice Dir, TipoDicionario A);
void QuickSort(TipoDicionario A, TipoIndice *n);
TipoIndice OrdenaPorFrequencia(TipoDicionario Vocabulario);
void GravaNumInt(FILE *ArqComprimido, int Num);
int LeNumInt(FILE *ArqComprimido);
int ConstroiVetores(TipoVetoresBO VetoresBaseOffset, TipoDicionario Vocabulario, int n, FILE *ArqComprimido);
int SegundaEtapa(TipoDicionario Vocabulario, TipoVetoresBO VetoresBaseOffset, TipoPesos p, FILE *ArqComprimido); 
void Escreve(FILE *ArqComprimido, int *Codigo, int *c);
int Codifica(TipoVetoresBO VetoresBaseOffset, int Ordem, int *c, int MaxCompCod);
void TerceiraEtapa(FILE *ArqTxt, TipoAlfabeto Alfabeto, int *TipoIndice, TipoPalavra Palavra, char *Linha, TipoDicionario Vocabulario, TipoPesos p, TipoVetoresBO VetoresBaseOffset, FILE *ArqComprimido, int MaxCompCod);
void Compressao(FILE *ArqTxt, FILE *ArqAlf, FILE *ArqComprimido);
int LeVetores(FILE *ArqComprimido, TipoBaseOffset *VetoresBaseOffset);
int LeVocabulario(FILE *ArqComprimido, TipoVetorPalavra Vocabulario);
void Atribui(TipoPadrao P, int Codigo, int c);