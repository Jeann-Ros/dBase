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
    novoArquivo->Sts = NULL;
    strcpy(novoArquivo->Data, date);
    strcpy(novoArquivo->Hora, timeStr);
    novoArquivo->Prox = NULL;
    novoArquivo->Ant = NULL;

    InserirArquivo(*unidade, novoArquivo);
}

void CreateFileFields(Arquivo **file) {
    // todo testar e aprimorar
    char fieldName[50];
    char fieldType[50];
    int width;
    int dec;
    char resp[2];
    do {
        printf("Criacao de campos para o arquivo %s\n", (*file)->NomeDBF);

        printf("Digite o nome do campo: ");
        gets(fieldName);

        printf("Digite o tipo do campo: ");
        gets(fieldType);

        printf("Digite a largura do campo: ");
        scanf("%d", &width);

        printf("Digite o numero de casas decimais: ");
        scanf("%d", &dec);

        Campos *campos = (Campos*)malloc(sizeof(Campos));

        strcpy(campos->FieldName, fieldName);
        strcpy(campos->Type, fieldType);
        campos->Width = width;
        campos->Dec = dec;
        campos->Patual = NULL;
        campos->Pdados = NULL;
        campos->Prox = NULL;

        printf("Deseja adicionar mais campos Y/N?: ");
        fflush(stdin);
        gets(resp);
    }
    while (strcmp(resp, "Y") == 0);
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