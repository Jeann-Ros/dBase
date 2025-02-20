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