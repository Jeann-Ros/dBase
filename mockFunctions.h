void MockInserirStatus(Arquivo **file) {

    Status *statusAtual = (*file)->Sts;
    Status *novoStatus = (Status*)malloc(sizeof(Status));

    novoStatus->Prox= NULL;
    novoStatus->Val[0] = '0';
    novoStatus->Val[1] = '\0';

    if (statusAtual == NULL) {
        (*file)->Sts = novoStatus;
    } else {
        while (statusAtual->Prox != NULL) {
            statusAtual = statusAtual->Prox;
        }

        statusAtual->Prox = novoStatus;
    }
}

void MockCreateFileFields(Arquivo **file) {
    // crie manualmente tres campos para o arquivo
    Campos *campo1 = (Campos*)malloc(sizeof(Campos));
    Campos *campo2 = (Campos*)malloc(sizeof(Campos));
    Campos *campo3 = (Campos*)malloc(sizeof(Campos));

    strcpy(campo1->FieldName, "Nome");
    strcpy(campo1->Type, "C");
    campo1->Width = 50;
    campo1->Dec = 0;
    campo1->Patual = NULL;
    campo1->Pdados = NULL;
    campo1->Prox = campo2;
    MockInserirStatus(file);

    strcpy(campo2->FieldName, "Idade");
    strcpy(campo2->Type, "N");
    campo2->Width = 0;
    campo2->Dec = 0;
    campo2->Patual = NULL;
    campo2->Pdados = NULL;
    campo2->Prox = campo3;
    MockInserirStatus(file);

    strcpy(campo3->FieldName, "DataNascimento");
    strcpy(campo3->Type, "D");
    campo3->Width = 0;
    campo3->Dec = 0;
    campo3->Patual = NULL;
    campo3->Pdados = NULL;
    campo3->Prox = NULL;
    MockInserirStatus(file);

    (*file)->Cmp = campo1;
}

void MockCreateDbfFile(Unidade **unidade){
    time_t now;
    struct tm *local;
    char date[20], timeStr[20];

    time(&now);

    local = localtime(&now);

    strftime(date, sizeof(date), "%d-%m-%Y", local);
    strftime(timeStr, sizeof(timeStr), "%H:%M:%S", local);

    Arquivo *novoArquivo = (Arquivo*)malloc(sizeof(Arquivo));

    strcpy(novoArquivo->NomeDBF, "MOCK.DBF");
    novoArquivo->Cmp = NULL;
    MockCreateFileFields(&novoArquivo);
    novoArquivo->Sts = NULL;
    strcpy(novoArquivo->Data, date);
    strcpy(novoArquivo->Hora, timeStr);
    novoArquivo->Ant = novoArquivo->Prox = NULL;

    InserirArquivo(*unidade, novoArquivo);
}

