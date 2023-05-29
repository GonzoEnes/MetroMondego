//
// Created by Goncalo on 17/04/2023.
//

#include "linhas.h"

int isListEmpty(pLinha linhas){
    if(linhas == NULL){
        return 1;
    }
    return 0;
}

void freeLinhas(pLinha linhas){
    pLinha linhasTemp;

    while (linhas != NULL){
        linhasTemp = linhas;

        linhas = linhas->prox;

        free(linhasTemp);
    }
}

int contemParagem(pLinha head, char* codigoParagem){
    pLinha aux = head;
    while(aux != NULL){
        for (int i = 0; i < aux->nParagens; i++){
            if(strcmp(aux->paragens[i].codigo, codigoParagem) == 0){
                return 1;
            }
        }
        aux = aux->prox;
    }
    return -1;
}

int doesLinhaExist(pLinha head, char* nomeLinha){
    while (head != NULL){
        if(strcmp(head->nomeLinha, nomeLinha) == 0){ // se ja existir essa
            printf("\n[ERRO] Nao foi possivel adicionar linha [%s]. Ja existe na lista.\n", nomeLinha);
            return 1;
        }
        head = head->prox;
    }
    return 0;
}

void calculaParagensSemOverflow(pLinha head, char* nomePartida, char* nomeDestino){
    pLinha aux = head;
    int indexStartPoint, indexEndPoint;

    if (strcmp(nomePartida, nomeDestino) == 0){
        printf("\n[ERRO] Insira nome de partida e nome de destino diferente!\n");
        return;
    }

    if (isListEmpty(head) == 1){
        printf("\n[ERRO] Nao existem linhas no sistema! Crie-as!\n");
        return;
    }

    if(aux->paragens == NULL){
        printf("\n[ERRO] [%s] nao contem paragens. Experimente adiciona-las!", aux->nomeLinha);
        return;
    }

    while(aux != NULL){
        for (int i = 0; i < aux->nParagens; i++){
            if (strcmp(aux->paragens[i].nome, nomePartida) == 0){
                indexStartPoint = i;
                // printf("\nIndex start: %d\n", indexStartPoint);
                for(int j = i; j < aux->nParagens + indexStartPoint; j++){
                    int indexSave = j % aux->nParagens;
                    if(strcmp(aux->paragens[indexSave].nome, nomeDestino) == 0){
                        indexEndPoint = indexSave; // para nao se perder o endPoint
                        //printf("\nIndex end: %d\n", indexEndPoint);
                        if(indexStartPoint < indexEndPoint){ // se correr tudo normalmente e o inicio estiver antes do fim, então:
                            printf("\n------------------------------------------------------------------------------\n");
                            printf("\n[NOTIFICACAO] Este percurso pode ser feito pela linha: [%s]", aux->nomeLinha);
                            printf("\nA listar todo o percurso que fara entre [%s] -> [%s]", nomePartida, nomeDestino);

                            printf("\n[%s]", nomePartida);

                            while (indexStartPoint < indexEndPoint){
                                //indexStartPoint++;
                                printf(" -> [%s]", aux->paragens[++indexStartPoint].nome);
                            }
                            printf("\n\n------------------------------------------------------------------------------\n");
                            break;
                        }
                        else if(indexStartPoint > indexEndPoint){ // se o inicio estiver depois do fim
                            printf("\n------------------------------------------------------------------------------\n");
                            printf("\n[NOTIFICACAO] Este percurso pode ser feito pela linha: [%s]\n", aux->nomeLinha);
                            printf("\nA listar todo o percurso que fara entre [%s] -> [%s]\n\n", nomePartida, nomeDestino);

                            // print stops from starting point to end of array
                            for(int k = indexStartPoint; k < aux->nParagens; k++){
                                printf("-> [%s] ", aux->paragens[k].nome);
                            }

                            // print stops from beginning of array to ending point
                            for(int l = 0; l <= indexEndPoint; l++){
                                printf("-> [%s] ", aux->paragens[l].nome);
                            }

                            // print ending stop
                            printf("\n------------------------------------------------------------------------------\n");
                            break;
                        }
                    }
                    else{
                        //printf("\nOla\n");
                        continue;
                    }
                }
            }
        }
        aux = aux->prox;
    }
}

void decrementaFromSystem(pParagem p, pLinha head, int totalParagens){
    for (int x = 0; x < totalParagens; x++){
        for (int k = 0; k < head->nParagens; k++){
            if(strcmp(p[x].nome, head->paragens[k].nome) == 0 && p[x].nLinhas > 0){
                p[x].nLinhas--;
            }
        }
    }
}

pLinha criaLinha(pLinha head, pParagem p, int totalParagens){

    pLinha novo, aux = NULL;
    paragem novaParagem;
    int cont = 0;
    //char nomeParagem[MAX];

    novo = malloc(sizeof(linha));

    if (novo == NULL){
        printf("\n[ERRO] Alocacao de memoria para nova linha!\n");
        return head;
    }

    printf("\nQual o nome da linha? \n");

    scanf(" %s", novo->nomeLinha);

    novo->prox = NULL;

    if (doesLinhaExist(head, novo->nomeLinha) == 1) { // linha já existe
        free(novo);
        return head;
    }

    if (totalParagens == 0){
        printf("\n[ERRO] Nao e possivel criar uma linha sem paragens existentes no sistema.\n");
        return head;
    }

    printf("\nQuantas paragens deseja adicionar? Existem %d paragens no sistema.\n", totalParagens);

    scanf(" %d", &cont);

    if(cont <= totalParagens){

        novo->nParagens = cont;

        novo->paragens = malloc(novo->nParagens * sizeof(paragem)); // aloca espaço para as paragens dessa linha

        if(novo->paragens == NULL) {
            printf("\n[ERRO] Alocacao de espaco para as paragens da linha [%s]\n", novo->nomeLinha);
            free(novo);
            return head;
        }

        for (int i = 0; i < novo->nParagens; i++){
            printf("\nInsira o nome da %da paragem a adicionar: ", i+1);
            scanf(" %s", novo->paragens[i].nome);

            /*if(strcmp(novo->paragens[i].nome, nomeParagem) == 0){ // verificar se essa paragem já foi adicionada aquando a criação DAR DEBUG
                printf("\n[ERRO] Esta paragem ja se encontra na linha!\n");
                decrementaFromSystem(p, novo, totalParagens);
                return head;
            }*/

            int index = checkIfExistsByName(p, novo->paragens[i].nome, totalParagens); // verifica se existe essa paragem no sistema

            if (index != -1){
                novaParagem = p[index]; // vai buscar essa paragem ao indice de onde a encontrou no sistema

                novo->paragens[i] = novaParagem;
                novo->paragens[i].nLinhas++;
                p[index].nLinhas++; // incrementa nLinhas for the added paragem

                printf("\n[SUCESSO] Paragem [%s] adicionada a linha [%s]!\n", novaParagem.nome, novo->nomeLinha);
            }
            else {
                printf("\n[ERRO] ABORTADO CRIACAO DA LINHA [%s]. Esta a tentar adicionar uma paragem que nao existe no sistema ainda! Experimente cria-la!\n", novo->nomeLinha);
                decrementaFromSystem(p, novo, totalParagens);
                free(novo);
                return head;
            }
        }

        if (head == NULL){ // se a lista estiver vazia
            head = novo; // mete a root como o novo elemento, porque é o único que existe
        }
        else {
            aux = head; // para não perder o início da lista
            while(aux->prox != NULL){ // se não estiver, percorre todos os nos ate ao fim da lista
                aux = aux->prox;
            }
            aux->prox = novo; // adiciona no fim da lista
        }

        return head;
    }
    else
    {
        printf("\n[ERRO] Esta a tentar adicionar mais paragens a linha [%s] do que existem no sistema!", novo->nomeLinha);
        free(novo);
        return head;
    }
}

pLinha removeParagemFromLinha(pLinha head, int quant, char* nomeLinha){ // esta lógica tem de ser toda mudada, ele esta a criar uma paragem Ourem nova e não a adicionar uma já existente.
    pLinha aux = head;
    char codigoParagem[MAX];

    if (isListEmpty(head) == 1){
        printf("\n[ERRO] Lista vazia.\n");
        return head;
    }

    while(aux != NULL){ // enquanto tiver linhas
        if(strcmp(aux->nomeLinha, nomeLinha) == 0){ // encontra a linha que o user input
            printf("\nInsira o codigo da paragem a remover: ");
            scanf(" %s", codigoParagem);
            if (quant > aux->nParagens) {
                printf("\n[ERRO] Esta a tentar remover mais paragens que a linha contem.\n");
                return head;
            }
            while(aux->nParagens >= quant && quant > 0){ // enquanto a quantidade que o user inseriu for menor que o numero total de paragens e maior que 0
                aux->paragens = removeParagem(aux->paragens, codigoParagem, &aux->nParagens); // atualiza a lista e remove as paragens indicadas pelo user.
                quant--; // reduz o cont // VER MELHOR
            }
        }
        aux = aux->prox;
    }
    return head;
}

/* ANTIGO
 * pParagem removeParagemFromLinha(pParagem p, pLinha head, int tam, char* nomeLinha){ // esta lógica tem de ser toda mudada, ele esta a criar uma paragem Ourem nova e não a adicionar uma já existente.
    pLinha aux = head;
    char codigoParagem[MAX];
    int index;
    paragem retorna;

    pParagem auxP = NULL;

    printf("\nInsira o codigo da paragem: ");
    scanf(" %s", codigoParagem);

    /*if (contemParagem(head, codigoParagem) == -1) {
        printf("\n[ERRO] Impossivel remover uma paragem que nao existe na linha %s.\n", nomeLinha);
        return aux->paragens;
    } ainda nao sei se isto é preciso

    while (aux != NULL) {
        if (strcmp(aux->nomeLinha, nomeLinha) == 0) {
            index = checkIfExistsByCode(aux->paragens, codigoParagem, aux->nParagens);
            if (index == -1) {
                printf("\n[ERRO] Nao encontro a paragem de codigo [%s]", codigoParagem);
                return aux->paragens;
            }

            retorna = aux->paragens[index];

            p[index].nLinhas--;

            aux->nParagens--;

            auxP = realloc(aux->paragens, (aux->nParagens) * sizeof(struct paragens));

            if (auxP == NULL) {
                printf("\n[ERRO] Alocacao de memoria para remover paragem de linha [%s]", nomeLinha);
                p[index].nLinhas++;
                aux->nParagens++;
                // guardar a posição que removeu se falhar para depois voltar a por no sitio obv
                return aux->paragens;
            }
        }
        aux = aux->prox;
    }
}*/

pParagem addParagemToLinha(pParagem p, pLinha head, int tam, char* nomeLinha) {
    char codigoParagem[MAX];
    pLinha aux = head;
    int index;
    pParagem auxP = NULL;

    printf("\nInsira o codigo da paragem: ");
    scanf(" %s", codigoParagem);

    if (contemParagem(head, codigoParagem) != -1) {
        printf("\n[ERRO] Paragem de codigo [%s] ja existe na linha [%s]!\n", codigoParagem, nomeLinha);
        return aux->paragens;
    }

    while (aux != NULL) {
        if (strcmp(aux->nomeLinha, nomeLinha) == 0) {
            index = checkIfExistsByCode(p, codigoParagem, tam);
            if (index == -1) {
                printf("\n[ERRO] Paragem nao existe no sistema.\n");
                return aux->paragens;
            }

            p[index].nLinhas++;

            aux->nParagens++;

            auxP = realloc(aux->paragens, (aux->nParagens) * sizeof(struct paragens));

            printf("Valor: %d", aux->nParagens);

            if (auxP == NULL) {
                printf("\n[ERRO] Alloc de memoria.\n");
                p[index].nLinhas--;
                aux->nParagens--;
                return aux->paragens;
            }

            aux->paragens[aux->nParagens - 1] = p[index];

            return auxP;
        }
        aux = aux->prox;
    }
    return auxP;
}

pLinha addToEndOfList(pLinha head, pLinha novoNo) {
    pLinha aux = NULL;

    if (head == NULL) {
        head = novoNo;
        return head;
    }

    aux = head;

    while (aux->prox != NULL) {
        aux = aux->prox;
    }

    aux->prox = novoNo;

    return head;
}

pLinha rebuildLinhaFromFile(char* fileName) {
    pLinha novo, p = NULL;

    linha novoLinha;

    FILE *f;

    f = fopen(fileName, "rb");

    if (f == NULL) {
        printf("\n[ERRO] Nao existe ficheiro [%s]", fileName);
        return NULL;
    }

    while (fread(&novoLinha, sizeof(linha), 1, f) == 1) {

        novo = malloc(sizeof(struct linhas));

        if (novo == NULL) {
            printf("\n[ERRO] Alocacao de memoria para nova linha! (REBUILD LINHA FROM FILE)\n");
            fclose(f);
            return p;
        }

        *novo = novoLinha;

        novo->paragens = malloc(novo->nParagens * sizeof(paragem));

        if (novo->paragens == NULL) {
            printf("\n[ERRO] Alocacao de memoria array dinamico de linha.\n");
            free(novo);
            fclose(f);
            return NULL;
        }

        if (fread(novo->paragens, sizeof(paragem), novo->nParagens, f) != novo->nParagens) {
            printf("\n[ERRO] Leitura do array dinamico de paragens.\n");
            free(novo->paragens);
            free(novo);
            fclose(f);
            return NULL;
        } // ler de novo para ir agora buscar as paragens de cada no

        novo->prox = NULL;

        p = addToEndOfList(p, novo);
    }

    fclose(f);

    return p;
}

pLinha addParagensToLinhaRefresh(pParagem p, pLinha head, int quant, char* nomeLinha, int totalParagens){
    pLinha aux = head;

    if (isListEmpty(head) == 1){
        printf("\n[ERRO] Nao existem linhas no sistema atualmente. Nada a adicionar.\n");
        return head;
    }

    if (quant > totalParagens) {
        printf("\n[ERRO] Nao pode adicionar mais paragens a linha do que ja existem.\n");
        return head;
    }

    while(aux != NULL){
        if (strcmp(aux->nomeLinha, nomeLinha) == 0){
            while(totalParagens >= quant && quant > 0){
                aux->paragens = addParagemToLinha(p, aux, totalParagens, nomeLinha);
                quant--;
            }
        }
        aux = aux->prox;
    }
    printf("Adicionado a linha [%s] com sucesso.\n", nomeLinha);
    return head;
}

pLinha removeLinha(pLinha head){
    pLinha aux = head, anterior;
    char nomeLinha[MAX];

    if(isListEmpty(head) == 1){
        printf("\n[ERRO] Nada a remover. Nao existem linhas no sistema.\n");
        return head;
    }

    printf("\nInsira o nome da linha que deseja remover: ");
    scanf(" %s", nomeLinha);

    if (aux != NULL && strcmp(aux->nomeLinha, nomeLinha) == 0){ // se o nó a remover for a raiz então
        head = aux->prox; // a raiz é o proximo no (NULL)
        free(aux); // libertamos o espaço da "raiz"
        return head;
    }

    while(aux != NULL && strcmp(aux->nomeLinha, nomeLinha) != 0){ // vai tentando encontrar o nome a remover na lista inteira...
        anterior = aux;
        aux = aux->prox;
    }

    if (aux == NULL){ // se nao encontrar sai
        printf("\n[ERRO] Linha nao existe no sistema. Nao consegui remover.\n");
        return head;
    }

    // se encontrou, entao:
    anterior->prox = aux->prox; // arrancamos
    free(aux);
    printf("\nLinha removida com sucesso.\n");
    return head; // devolve a lista atualizada
}

void listaAllLinhaInfo(pLinha head, pParagem p, int totalParagens){
    pLinha aux = head;
    printf("\nA LISTAR INFO DE TODAS AS LINHAS\n");
    while(aux != NULL){
        if(aux->nParagens > 0) {
            printf("-----------------------------------------------------");
            printf("\nNome da linha: [%s]\n", aux->nomeLinha);
            printf("\nPossui [%d] paragens.\n", aux->nParagens);
            printf("\nAqui estao: ");
            listaParagemSys(aux->paragens, aux->nParagens);
            printf("-----------------------------------------------------");
        }
        else {
            printf("\nNome da linha: [%s]", aux->nomeLinha);
            printf("\nPossui [%d] paragens.\n", aux->nParagens);
            printf("\n[WARNING] Esta linha nao contem paragens.\n");
        }
        aux = aux->prox;
    }
}

void listaInfoLinha(pLinha head, pParagem p, int totalParagens){ //dividir melhor esta função para não ficar tão grande quando tiver tempo
    char userChoice[MAX], nomeParagem[MAX];

    int index; //, numLinhas = 0, flag = 0;

    if (isListEmpty(head) == 1){
        printf("[WARNING] Nada a listar. Nao existem linhas no sistema. Experimente cria-las!");
        return;
    }

    printf("\nDeseja listar as linhas que passam numa determinada paragem ou todas?\n");

    printf("Escreva [paragem] ou [todas] para confirmar a selecao\n");

    do {
        scanf(" %s", userChoice);

        if (strcmp(userChoice, "paragem") != 0 && strcmp(userChoice, "todas") != 0){
            printf("\nInsira [paragem] ou [todas]: ");
        }
    }while(strcmp(userChoice, "paragem") != 0 && strcmp(userChoice, "todas") != 0);

    if(strcmp(userChoice, "todas") == 0){
        listaAllLinhaInfo(head, p, totalParagens);
    }

    else if (strcmp(userChoice, "paragem") == 0){
        do{
            printf("\nInsira o nome da paragem a procurar: ");

            scanf(" %s", nomeParagem);

            listaInfoLinhaByParagem(head, p, totalParagens, nomeParagem);
                //printf("\nTotal: [%d] linhas passam por [%s]\n", numLinhas, nomeParagem); ARRANJAR MANEIRA DE PRINTAR ISTO
            if (strcmp(nomeParagem, "fim") == 0){
                printf("A interromper a listagem...\n");
            }
        }while(strcmp(nomeParagem, "fim") != 0);
    }
}

void listaInfoLinhaByParagem(pLinha head, pParagem p, int totalParagens, char nomeParagem[MAX]){
    pLinha aux;

    if(contemParagem(head, nomeParagem) == -1){
        printf("\n[ERRO] Linha nao contem paragens!\n");
        return;
    }

    int index = checkIfExistsByName(p, nomeParagem, totalParagens); // verifica se essa paragem existe no sistema

    if (index != -1){ // existe no sistema
        printf("\nParagem registada, a mostrar linhas que passam em [%s]...\n", nomeParagem);
        aux = head;
        while(aux != NULL){
            for (int i = 0; i < aux->nParagens; i++){
                if(strcmp(nomeParagem, aux->paragens[i].nome) == 0){
                    printf("\nNome linha: [%s]\n", aux->nomeLinha);
                    printf("Numero de paragens: [%d]\n", aux->nParagens);
                }
                /*else { // dar fix a este else
                    if(flag == 0){
                        printf("\n[ERRO] Nenhuma linha contem a paragem descrita.\n");
                        flag = 1;
                    }

                }*/
            }
            aux = aux->prox;
        }
    } else {
        printf("[ERRO] Paragem nao existe no sistema.\n");
        return;
    }
}