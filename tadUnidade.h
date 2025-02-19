void Init(Unidade **U){
	Unidade *NovaD,*NovaC;
	NovaD = (Unidade*)malloc(sizeof(Unidade));
	strcpy(NovaD->und, "D:");
	NovaD->top = NULL;
	NovaD->Arq = NULL;

	NovaC = (Unidade*)malloc(sizeof(Unidade));
	strcpy(NovaC->und, "C:");
	NovaC->bottom = NULL;
	NovaC->Arq = NULL;
	
	NovaD->bottom = NovaC;
	NovaC->top = NovaD;
	
	*U = NovaD;
}

void SetDefault(Unidade **U, char dest[3]){

	if(strcmp((*U)->und, dest) != 0){
		if(strcmp((*U)->und, "D:") == 0){
			*U = (*U)->bottom;
		}else{
			*U = (*U)->top;
		}
	}
}

void ExibirUnidade(Unidade *U){
	printf("Unidade: %s\n", U->und);
}

void InserirArquivo(Unidade *U, Arquivo *novoArquivo) {
	Arquivo *arquivos = U->Arq;

	if (arquivos == NULL) {
		U->Arq = novoArquivo;
	} else {
		while (arquivos->Prox != NULL) {
			arquivos = arquivos->Prox;
		}

		arquivos->Prox = novoArquivo;
		novoArquivo->Ant = arquivos;
		novoArquivo->Prox = NULL;
	}
}
