#include <stdlib.h>
#include <conio2.h>
#include <string.h>
#include <stdio.h>
#include "structs.h"
#include "tadUnidade.h"


//Quais os passos?
/*

	1 - Vou precisar que as unidades sejam criadas com o *Arq apontando para nulo. Preciso que o usuário possa mudar de unidade com o comando SET DEFAULT TO
		- Criar uma função InitDb que cria as duas unidades
	
	2 - Com a função CREATE o usuário vai poder criar um arquivo na unidade onde U está apontando

*/

int main(){
	
	Unidade *U;
	char comando[120];
	
	Init(&U);
	while(strcmp(comando, "QUIT") != 0){
		fflush(stdin);
		gets(comando);
		printf("comando lido: %s", comando);
	}
	
}
