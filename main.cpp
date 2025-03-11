#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include "structs.h"
#include "tadUnidade.h"
#include "tadArquivo.h"
#include "linhasManager.h"
#include "fileManager.h"
#include "mockFunctions.h"

char validarNomeNovoArquivo(char *nomeArquivo) {
	if(strlen(nomeArquivo) > 50){
		printf("Nome do arquivo muito grande, tente novamente\n");
		return 0;
	}

	if(nomeArquivo[strlen(nomeArquivo) - 4] != '.' || nomeArquivo[strlen(nomeArquivo) - 3] != 'D' || nomeArquivo[strlen(nomeArquivo) - 2] != 'B' || nomeArquivo[strlen(nomeArquivo) - 1] != 'F'){
		printf("Nome do arquivo invalido, tente novamente\n");
		return 0;
	}

	return 1;
}

char validarValorDeBusca(char *valorBusca) {
	if (valorBusca[0] == '"' && valorBusca[strlen(valorBusca) - 1] == '"')
		return 1;
	return 0;
}

void removeQuotes(char *str) {
	int i, j = 0;
	for (i = 0; str[i] != '\0'; i++) {
		if (str[i] != '"') {
			str[j++] = str[i];
		}
	}
	str[j] = '\0';
}

void interpretarComando(char command[50][50], Unidade **unidade, Arquivo **arqAberto, char devMode, Status **status, int *setDeleted){
    if(strcmp(command[0], "SET") == 0 && strcmp(command[1], "DEFAULT") == 0 && strcmp(command[2], "TO") == 0) {
	    SetDefault(&(*unidade), command[3]);
    	return ExibirUnidade(*unidade);
    }

	if (strcmp(command[0], "LOCATE") == 0 && strcmp(command[1], "FOR") == 0 && strcmp(command[3], "=") == 0 ) {
		if (*arqAberto == NULL) {
			printf("Nenhum arquivo aberto\n");
		}else if (validarValorDeBusca(command[4])) {
			removeQuotes(command[4]);
			return SearchForFieldValue(command[2], command[4], *arqAberto);
		}
		else{
			printf("Valor de buscas invalido\n");
		}
	}

	if (strcmp(command[0], "LIST") == 0 && strcmp(command[1], "FOR") == 0 && strcmp(command[3], "=") == 0 ) {
		if (*arqAberto == NULL) {
			printf("Nenhum arquivo aberto\n");
		}else if (validarValorDeBusca(command[4])) {
			removeQuotes(command[4]);
			return SearchForFieldMatch(command[2], command[4], *arqAberto);
		}
		else{
			printf("Valor de buscas invalido\n");
		}
	}

	// "macacos loucos"
	// considerar nomes com espaco
	if (strcmp(command[0], "CREATE") == 0) {
		if (devMode) {
			return MockCreateDbfFile(&(*unidade));
		}

		if(validarNomeNovoArquivo(command[1]))
			return CreateDbfFile(&(*unidade), command[1]);
	}

	if (strcmp(command[0] , "DIR") == 0) {
		return ListFiles(*unidade);
	}

	if (strcmp(command[0] , "USE") == 0) {
		return OpenFile(*unidade, command[1], &(*arqAberto));
	}

	if (strcmp(command[0], "APPEND") == 0) {
		if (*arqAberto == NULL) {
			printf("Nenhum arquivo aberto\n");
		} else {
			return AppendData(*arqAberto);
		}
	}

	if (strcmp(command[0], "LIST") == 0 && strcmp(command[1], "STRUCTURE") == 0) {
		if (*arqAberto == NULL) {
			printf("Nenhum arquivo aberto\n");
		}else {
			return ExibirCamposDoArquivo(*arqAberto);
		}
	}

	if (strcmp(command[0], "GOTO") == 0) {
		if (*arqAberto == NULL) {
			printf("Nenhum arquivo aberto\n");
		}else {
			return LocalizarRegistro(&(*arqAberto), atoi(command[1]), &(*status));
		}
	}

	if (strcmp(command[0], "DISPLAY") == 0) {
		if (*arqAberto == NULL) {
			printf("Nenhum arquivo aberto\n");
		}else {
			return MostrarRegistro(*arqAberto);
		}
	}

	if (strcmp(command[0], "LIST") == 0) {
		if (*arqAberto == NULL) {
			printf("Nenhum arquivo aberto\n");
		}else {
			return ListFileData(*arqAberto, *setDeleted);
		}
	}

	if (strcmp(command[0], "EDIT") == 0) {
		if (*arqAberto == NULL) {
			printf("Nenhum arquivo aberto\n");
		}else {
			return EditarRegistro(&(*arqAberto));
		}
	}

	if (strcmp(command[0], "ZAP") == 0) {
		if (*arqAberto == NULL) {
			printf("Nenhum arquivo aberto\n");
		}else {
			return ExcluirRegistrosZap(&(*arqAberto));
		}
	}

	if (strcmp(command[0], "DELETE") == 0) {
		if (*arqAberto == NULL) {
			printf("Nenhum arquivo aberto\n");
		}else if (strcmp(command[1], "ALL") == 0) {
			DeletarTodosRegistrosLogico(&(*arqAberto));
		}else {
			DeletarRegistroLogico(&(*status));
		}
	}

	if (strcmp(command[0], "RECALL") == 0) {
		if (*arqAberto == NULL) {
			printf("Nenhum arquivo aberto\n");
		}else if (strcmp(command[1], "ALL") == 0) {
			RecallTodosRegistrosLogico(&(*arqAberto));
		}else {
			RecallRegistroLogico(&(*status));
		}
	}

	if (strcmp(command[0], "SET") == 0 && strcmp(command[1], "DELETED") == 0) {
		if (strcmp(command[2], "OFF") == 0) {
			*setDeleted = 0;
		}else if (strcmp(command[2], "ON") == 0) {
			*setDeleted = 1;
		}
	}
}

int main(){

	Unidade *U;
	char devMode = 1;
	char userInput[120];
	char command[50][50];
	int setDeleted = 0;
	Arquivo *arqAberto = NULL;
	Status *stsAtual = NULL;

	Init(&U);

	while(strcmp(userInput, "QUIT") != 0){
		fflush(stdin);
		gets(userInput);
		SalvarComando(command, userInput);
		interpretarComando(command, &U, &arqAberto, devMode, &stsAtual, &setDeleted);
	}

	#ifdef _WIN32
		system("cls");
	#elif __linux__ || __APPLE__
		system("clear");
	#endif

	return 0;
}