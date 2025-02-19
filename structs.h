union tipoDados{
	//N = number | D = date | L = logical | C = character | M = memo
	float N;
	char D[11], L[2], C[50], M[50];
};
typedef union tipoDados TipoDados;

struct dados{
	TipoDados valType;
	struct dados *Prox;
};
typedef struct dados Dados;

struct campos{
	char FieldName[50], Type[2];
	int Width, Dec; //Width = n�mero de caracteres dos campos | Dec = IDK
	Dados *Patual, *Pdados;
	struct campos *Prox;
};
typedef struct campos Campos;

struct status{
	char Val[2]; // 0 = True | Qualquer outro valor = False
	struct status *Prox;
};
typedef struct status Status;

struct arquivo{
	char NomeDBF[50], Data[11], Hora[6];
	struct arquivo *Ant, *Prox;
	Status *Sts;
	Campos *Cmp;
};
typedef struct arquivo Arquivo;

struct unidade{
	char und[3]; // Vamos ter apenas as unidades D: e C:
	struct unidade *top, *bottom;
	Arquivo *Arq;
};
typedef struct unidade Unidade;
