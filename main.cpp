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

void interpretarComando(char command[50][50], Unidade **unidade, Arquivo **arqAberto, char devMode){
    if(strcmp(command[0], "SET") == 0 && strcmp(command[1], "DEFAULT") == 0 && strcmp(command[2], "TO") == 0) {
	    SetDefault(&(*unidade), command[3]);
    	return ExibirUnidade(*unidade);
    }

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
			return LocalizarRegistro(&(*arqAberto), atoi(command[1]));
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
			return ListFileData(*arqAberto);
		}
	}

	if (strcmp(command[0], "EDIT") == 0) {
		if (*arqAberto == NULL) {
			printf("Nenhum arquivo aberto\n");
		}else {
			EditarRegistro(&(*arqAberto));
		}
	}
}

int main(){

	Unidade *U;
	char devMode = 1;
	char userInput[120];
	char command[50][50];
	Arquivo *arqAberto = NULL;

	Init(&U);

	while(strcmp(userInput, "QUIT") != 0){
		fflush(stdin);
		gets(userInput);
		SalvarComando(command, userInput);
		interpretarComando(command, &U, &arqAberto, devMode);
	}

	#ifdef _WIN32
		system("cls");
	#elif __linux__ || __APPLE__
		system("clear");
	#endif

	return 0;
}