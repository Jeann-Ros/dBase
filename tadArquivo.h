void InserirCampoDoArquivo(Arquivo **file, Campos *campo) {
    Campos *campos = (*file)->Cmp;

    if (campos == NULL) {
        (*file)->Cmp = campo;
    } else {
        while (campos->Prox != NULL) {
            campos = campos->Prox;
        }
        campos->Prox = campo;
    }
}

void ExibirCamposDoArquivo(Arquivo *file) {
    Campos *campo = file->Cmp;

    printf("NOME DO CAMPO \t TIPO \t LARGURA \t DECIMAIS\n");
    while (campo != NULL) {
        printf("%s \t %s \t %d \t %d\n", campo->FieldName, campo->Type, campo->Width, campo->Dec);
        campo = campo->Prox;
    }
}

void InserirDado(Campos **campo, Dados *dado) {
    Dados *dados = (*campo)->Pdados;

    if (dados == NULL) {
        (*campo)->Pdados = dado;
    } else {
        while (dados->Prox != NULL) {
            dados = dados->Prox;
        }

        dados->Prox = dado;
    }

    (*campo)->Patual = dado;
}

void InserirStatus(Arquivo **file) {

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

void ExibirDados(Campos *campo) {
    Dados *dados = campo->Pdados;
    int cont = 1;

    printf("DADOS DO CAMPO %s do tipo %s \n", campo->FieldName, campo->Type);
    while (dados != NULL) {
        if (campo->Type[0] == 'N')
            printf("%d \t %.2f\n", cont, dados->valType.N);
        if (campo->Type[0] == 'D')
            printf("%d \t %s\n", cont, dados->valType.D);
        if (campo->Type[0] == 'L')
            printf("%d \t %s\n", cont, dados->valType.L);
        if (campo->Type[0] == 'C')
            printf("%d \t %s\n", cont, dados->valType.C);
        if (campo->Type[0] == 'M')
            printf("%d \t %s\n", cont, dados->valType.M);

        dados = dados->Prox;
        cont++;
    }
}