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
		if(strcmp((*U)->und, "D:")){
			*U = (*U)->bottom;
		}else{
			*U = (*U)->top;
		}
	}
}
