void SepararLinha(char listaComando[50][50], const char* comando) {
    int i = 0, j = 0, k = 0;

    while (comando[i] != '\0') {
        if (comando[i] == ' ') {
            listaComando[j][k] = '\0';
            j++;
            k = 0;
        } else if (comando[i] == '"') {
            listaComando[j][k] = comando[i];
            k++;
            i++;
            while (comando[i] != '"' && comando[i] != '\0') {
                listaComando[j][k] = comando[i];
                k++;
                i++;
            }
            if (comando[i] == '"') {
                listaComando[j][k] = comando[i];
                k++;
            }
            listaComando[j][k] = '\0';
            j++;
            k = 0;
        } else {
            listaComando[j][k] = comando[i];
            k++;
        }
        i++;
    }
    listaComando[j][k] = '\0';
}
// list for nome = "macaco"
// list\0
//

void ZerarListaComando(char command[50][50]){
    for(int i = 0; i < 50; i++){
        for(int j = 0; j < 50; j++){
            command[i][j] = '\0';
        }
    }
}

void SalvarComando(char command[50][50], char comando[50]){
    ZerarListaComando(command);
    SepararLinha(command, comando);
}

void ExibirComando(char listaComando[50][50]){
    for(int i = 0; i < 50; i++){
        if(listaComando[i][0] != '\0'){
            printf("Comando %d: %s\n", i, listaComando[i]);
        }
    }
}
