void CreateFileFields(Arquivo **file) {
    // todo melhorar interface
    char fieldName[50];
    char fieldType[50];
    int width;
    int dec;
    char resp[2];
    do {
        printf("Criacao de campos para o arquivo %s\n", (*file)->NomeDBF);

        printf("Digite o nome do campo: ");
        fflush(stdin);
        gets(fieldName);

        printf("Digite o tipo do campo N/D/L/C/M: ");
        fflush(stdin);
        gets(fieldType);

        Campos *campos = (Campos*)malloc(sizeof(Campos));

        strcpy(campos->FieldName, fieldName);
        strcpy(campos->Type, fieldType);

        if (strcmp(fieldType, "N") == 0) {
            printf("Digite o numero de casas decimais: ");
            fflush(stdin);
            scanf("%d", &dec);
            campos->Dec = dec;
            campos->Width = 0;
        }
        else {
            printf("Digite a largura do campo: ");
            fflush(stdin);
            scanf("%d", &width);
            campos->Width = width;
            campos->Dec = 0;
        }

        campos->Patual = NULL;
        campos->Pdados = NULL;
        campos->Prox = NULL;


        InserirCampoDoArquivo(&(*file), campos);

        printf("Deseja adicionar mais campos Y/N?: ");
        fflush(stdin);
        gets(resp);
    }
    while (strcmp(resp, "Y") == 0);

}

void CreateDbfFile(Unidade **unidade, char *fileName){
    time_t now;
    struct tm *local;
    char date[20], timeStr[20];

    time(&now);

    local = localtime(&now);

    strftime(date, sizeof(date), "%d-%m-%Y", local);
    strftime(timeStr, sizeof(timeStr), "%H:%M:%S", local);

    Arquivo *novoArquivo = (Arquivo*)malloc(sizeof(Arquivo));

    strcpy(novoArquivo->NomeDBF, fileName);
    novoArquivo->Cmp = NULL;
    CreateFileFields(&novoArquivo);
    novoArquivo->Sts = NULL;
    strcpy(novoArquivo->Data, date);
    strcpy(novoArquivo->Hora, timeStr);
    novoArquivo->Ant = novoArquivo->Prox = NULL;

    InserirArquivo(*unidade, novoArquivo);
}

void ListFiles(Unidade *U){
    Arquivo *arquivos = U->Arq;
    if (arquivos == NULL) {
        printf("Nenhum arquivo encontrado\n");
    } else {
        printf("NOME \t DATA \t HORA\n");
        while (arquivos != NULL) {
            printf("%s \t %s \t %s \n", arquivos->NomeDBF, arquivos->Data, arquivos->Hora);
            arquivos = arquivos->Prox;
        }
    }
}

void OpenFile(Unidade *u, char *fileName, Arquivo **arqAberto) {
    Arquivo *arquivos = u->Arq;

    while (arquivos != NULL && strcmp(arquivos->NomeDBF, fileName) != 0) {
        arquivos = arquivos->Prox;
    }

    if (arquivos == NULL)
        printf("Arquivo nao encontrado\n");
    else {
        printf("Arquivo %s Carregado\n", arquivos->NomeDBF);
        *arqAberto = arquivos;
    }
}

void AppendData(Arquivo *arqAberto) {
    Campos *campos = arqAberto->Cmp;
    Dados *dado = (Dados*)malloc(sizeof(Dados));
    dado->Prox = NULL;

    printf("Iniciando insercao de dados no arquivo %s\n",arqAberto->NomeDBF);
    while (campos != NULL) {
        printf("Digite o valor do campo: %s do tipo %c\n", campos->FieldName, campos->Type[0]);

        if (campos->Type[0] == 'N') {
            fflush(stdin);
            scanf("%f", &dado->valType.N);
        }

        if (campos->Type[0] == 'D') {
            fflush(stdin);
            gets(dado->valType.D);
        }

        if (campos->Type[0] == 'L') {
            fflush(stdin);
            gets(dado->valType.L);
        }

        if (campos->Type[0] == 'C') {
            fflush(stdin);
            gets(dado->valType.C);
        }

        if (campos->Type[0] == 'M') {
            fflush(stdin);
            gets(dado->valType.M);
        }

        InserirDado(&campos, dado);
        InserirStatus(&arqAberto);
        campos = campos->Prox;
        dado = (Dados*)malloc(sizeof(Dados));
        dado->Prox = NULL;
    }
}

void ListFileData(Arquivo *arqAberto, int setDeleted) {
    int aux = 1;
    int auxCont;
    int arquivoCount = QuantidadeDeRegistros(arqAberto);
    Status *status = arqAberto->Sts;

    Campos *campos = NULL;
    Dados *dados = NULL;
    ExibirCabecalhoArquivo(arqAberto);

    while (aux <= arquivoCount) {
        campos = arqAberto->Cmp;
        if (strcmp(status->Val, "1") == 0 || setDeleted == 0) {
            printf("%d\t", aux);
        }

        while (campos != NULL) {
            auxCont = 1;
            dados = campos->Pdados;

            while (auxCont < aux) {
                dados = dados->Prox;
                auxCont++;
            }

            if (strcmp(status->Val, "1") == 0 || setDeleted == 0) {
                ExibirDadosFormatados(campos, dados);
                printf("\t");
            }

            campos = campos->Prox;
        }
        if (strcmp(status->Val, "1") == 0 || setDeleted == 0) {
            printf("\n");
        }
        status = status->Prox;
        aux++;
    }
}

Campos* FindFileField(Arquivo *arq, char *fieldName) {
    Campos *campos = arq->Cmp;

    while (campos != NULL && strcmp(campos->FieldName, fieldName) != 0) {
        campos = campos->Prox;
    }

    return campos;
}

void SearchForFieldValue(char *fieldName, char *searchText, Arquivo *arqAberto) {
    Campos *campo = FindFileField(arqAberto, fieldName);
    int posicao_dado = 0;
    int aux = 0;

    if (campo == NULL) {
        printf("Campo nao encontrado\n");
        return;
    }

    if (campo->Type[0] != 'C') {
        printf("Campo nao e do tipo Caractere\n");
        return;
    }

    Dados *dados = campo->Pdados;
    while (dados != NULL && strcmp(dados->valType.C, searchText) != 0) {
        dados = dados->Prox;
        posicao_dado++;
    }

    if (dados == NULL) {
        printf("Nenhum registro encontrado\n");
        return;
    }

    ExibirCabecalhoArquivo(arqAberto);
    printf("%d\t", posicao_dado + 1);
    while (campo != NULL) {
        aux = 0;
        dados = campo->Pdados;
        while (aux < posicao_dado) {
            dados = dados->Prox;
            aux++;
        }

        if (aux == posicao_dado) {
            ExibirDadosFormatados(campo, dados);
            printf("\t");
        }

        campo = campo->Prox;
    }
    printf("\n");
}

void SearchForFieldMatch(char *fieldName, char *searchText, Arquivo *arqAberto) {
    Campos *campo = FindFileField(arqAberto, fieldName);
    int posicao_dado = 0;
    int aux = 0;
    int listaRegistros[100];
    int listaRegistrosTL = 0;

    if (campo == NULL) {
        printf("Campo nao encontrado\n");
        return;
    }

    if (campo->Type[0] != 'C') {
        printf("Campo nao e do tipo Caractere\n");
        return;
    }

    Dados *dados = campo->Pdados;
    while (dados != NULL) {
        if (strstr(dados->valType.C, searchText) != NULL) {
            listaRegistros[listaRegistrosTL++] = posicao_dado;
        }
        dados = dados->Prox;
        posicao_dado++;
    }

    if (listaRegistrosTL == 0) {
        printf("Nenhum registro encontrado\n");
        return;
    }

    ExibirCabecalhoArquivo(arqAberto);
    for (int i = 0; i < listaRegistrosTL; i++) {
        campo = arqAberto->Cmp;
        printf("%d\t", listaRegistros[i] + 1);
        while (campo != NULL) {
            aux = 0;
            dados = campo->Pdados;
            while (aux < listaRegistros[i]) {
                dados = dados->Prox;
                aux++;
            }

            if (aux == listaRegistros[i]) {
                ExibirDadosFormatados(campo, dados);
                printf("\t");
            }

            campo = campo->Prox;
        }
        printf("\n");
    }
}