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
        printf("%s \t \t %s \t %d \t \t %d\n", campo->FieldName, campo->Type, campo->Width, campo->Dec);
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

void LocalizarRegistro(Arquivo **file, int pos) {
    Campos *campos = (*file)->Cmp;
    int init = 1;
    char flag = '0';

    if (campos == NULL) {
        printf("Nenhum campo localizado no arquivo.\n");
    }else {
        while (campos != NULL && flag == '0') {
            campos->Patual = campos->Pdados;
            init = 1;
            if (campos->Pdados == NULL) {
                flag = '1';
                printf("Nenhum registro localizado no arquivo.\n");
            }else {
                while (init<pos && campos->Patual -> Prox != NULL) {
                    init++;
                    campos->Patual = campos->Patual->Prox;
                }
                campos = campos->Prox;
            }
        }
    }
}

void MostrarRegistro(Arquivo *file) {
    //incluir lógica para mostrar número da linha do registro
    Campos *campos = file->Cmp, *fields = file->Cmp;
    char format[20];
    if (campos == NULL) {
        printf("Nenhum campo localizado no arquivo.\n");
    }else {
        while (fields != NULL) {
            printf("%s \t", fields->FieldName);
            fields = fields->Prox;
        }
        printf("\n");
        while (campos != NULL) {
            if (campos->Type[0] == 'N')
                printf("%.2f \t", campos->Patual->valType.N);
            if (campos->Type[0] == 'D')
                printf("%s \t", campos->Patual->valType.D);
            if (campos->Type[0] == 'L')
                printf("%s \t", campos->Patual->valType.L);
            if (campos->Type[0] == 'C')
                printf("%s \t", campos->Patual->valType.C);
            if (campos->Type[0] == 'M')
                printf("%s \t",  campos->Patual->valType.M);
            campos = campos->Prox;
        }
        printf("\n");
    }
}

void EditarRegistro(Arquivo **file) {
    Campos *campos = (*file)->Cmp;
    char input[50];
    float valorF;

    printf("Iniciando edicao de campos.\n");
    while (campos != NULL) {
        if (campos->Patual == NULL) {
            printf("Nenhum registro foi selecionado no arquivo.\n");
        }else {
            char valorS[campos->Width];
            printf("Campo %s\n", campos->FieldName);
            if (campos->Type[0] == 'N') {
                valorF = campos->Patual->valType.N;
                printf("Valor atual: %.2f\n", campos->Patual->valType.N);
                printf("Novo valor: ");
                fflush(stdin);
                fgets(input, sizeof(input), stdin);
                if (sscanf(input, "%f", &valorF) != 1){};
                campos->Patual->valType.N = valorF;
            }
            if (campos->Type[0] == 'D') {
                printf("Valor atual: %s\n", campos->Patual->valType.D);
                printf("Novo valor: ");
                fflush(stdin);
                gets(valorS);
                if (strlen(valorS) > 0) {
                    strcpy(campos->Patual->valType.D, valorS);
                }
            }
            if (campos->Type[0] == 'L') {
                printf("Valor atual: %s\n", campos->Patual->valType.L);
                printf("Novo valor: ");
                fflush(stdin);
                gets(valorS);
                if (strlen(valorS) > 0) {
                    strcpy(campos->Patual->valType.L, valorS);
                }
            }
            if (campos->Type[0] == 'C') {
                printf("Valor atual: %s\n", campos->Patual->valType.C);
                printf("Novo valor: ");
                fflush(stdin);
                gets(valorS);
                if (strlen(valorS) > 0) {
                    strcpy(campos->Patual->valType.C, valorS);
                }
            }
            if (campos->Type[0] == 'M') {
                printf("Valor atual: %s\n",  campos->Patual->valType.M);
                printf("Novo valor: ");
                fflush(stdin);
                gets(valorS);
                if (strlen(valorS) > 0) {
                    strcpy(campos->Patual->valType.M, valorS);
                }
            }

            campos = campos->Prox;
        }
    }
}