#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "structs.h"
#include "tadUnidade.h"
#include "linhasManager.h"

//Quais os passos?
/*

	0 - Criar uma funcao que vai receber toda a string que o usuario digitar e vai separar em um vetor de palavras[][], com base nesse vetor eu vou validar os comandos
	que eu quero executar
		- Vou precisar de varios ifs para executar os comandos de maneira correta

	1 - Vou precisar que as unidades sejam criadas com o *Arq apontando para nulo. Preciso que o usuario possa mudar de unidade com o comando SET DEFAULT TO
		- Criar uma funcao InitDb que cria as duas unidades
		- Criar uma funcao para ser chamada pelo main que vai mudar a unidade do usuario
	
	2 - Com a funcao CREATE o usuario vai poder criar um arquivo na unidade onde U esta apontando
		- Como que eu coloco os dados dentro do arquivo?
		
	3- DIR vai ser o comando que vai listar todos os arquivos da unidade que esta sendo apontada
		- Criar uma funcao que varre toda a lista e exibe aqueles que estamos apostando
		
	4 - QUIT eh o comado que encerra o dBase, acho que vamos precisar limpar a memoria com o heap ccom free()
	
	5 - USE eh o comando que vai abrir um arquivo da unidade
	
	6 - LIST STRUCTURE eh o comando que vai listar a estrutura (campos, tipos, tamanhos e 'dec') do arquivo que esta aberto
	
	7 - APPEND insere um novo registro no final do arquivo, este registro sao os dados que o arquivo armazena
	
	8 - 

*/

void interpretarComando(char command[50][50], Unidade **unidade){
    if(strcmp(command[0], "SET") == 0 && strcmp(command[1], "DEFAULT") == 0 && strcmp(command[2], "TO") == 0) {
	    SetDefault(&(*unidade), command[3]);
    	ExibirUnidade(*unidade);
    }
}
int main(){

	Unidade *U;
	char userInput[120];
	char command[50][50];

	Init(&U);

	while(strcmp(userInput, "QUIT") != 0){
		fflush(stdin);
		gets(userInput);
		SalvarComando(command, userInput);
		interpretarComando(command, &U);
	}
	
}