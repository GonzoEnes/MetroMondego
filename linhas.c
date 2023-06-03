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

    while (aux != NULL) {
        for (int i = 0; i < aux->nParagens; i++) {
            if (strcmp(nomePartida, aux->paragens[i].nome) == 0) {
                for (int j = (i + 1) % aux->nParagens; j != i; j = (j + 1) % aux->nParagens) {
                    if (strcmp(nomeDestino, aux->paragens[j].nome) == 0) {
                        printf("\n------------------------------------------------------------------------------\n");

                        printf("\n[NOTIFICACAO] Este percurso pode ser feito pela linha: [%s]", aux->nomeLinha);

                        printf("\nA listar todo o percurso que fara entre [%s] a [%s]\n", nomePartida, nomeDestino);

                        if (i < j) {
                            printf("[%s] ->", nomePartida);
                            for (int k = i + 1; k < j; k++) {
                                printf(" [%s] -> ", aux->paragens[k].nome);
                            }
                            printf(" [%s] \n", nomeDestino);
                        } else {
                            printf("[%s] ->", nomePartida);
                            for (int k = i - 1; k != j; k = (k - 1 + aux->nParagens) % aux->nParagens) {
                                printf(" [%s] -> ", aux->paragens[k].nome);
                            }
                            printf(" [%s] \n", nomeDestino);
                        }
                        // Encerra a função após imprimir os elementos
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

    fflush(stdin);

    fgets(novo->nomeLinha, sizeof(novo->nomeLinha), stdin);

    novo->nomeLinha[strcspn(novo->nomeLinha, "\n")] = 0;

    novo->prox = NULL;

    if (doesLinhaExist(head, novo->nomeLinha) == 1) { // linha já existe
        printf("\n[ERRO] Nao pode criar uma linha com nome igual a outra que ja existe.\n");
        free(novo);
        return head;
    }

    if (totalParagens == 0){
        printf("\n[ERRO] Nao e possivel criar uma linha sem paragens existentes no sistema.\n");
        return head;
    }

    printf("\nQuantas paragens deseja adicionar? Existem %d paragens no sistema.\n", totalParagens);

    scanf(" %d", &cont);

    if(cont <= totalParagens && cont > 0){

        novo->nParagens = cont;

        novo->paragens = malloc(novo->nParagens * sizeof(paragem)); // aloca espaço para as paragens dessa linha

        if(novo->paragens == NULL) {
            printf("\n[ERRO] Alocacao de espaco para as paragens da linha [%s]\n", novo->nomeLinha);
            free(novo);
            return head;
        }

        for (int i = 0; i < novo->nParagens; i++){
            printf("\nInsira o nome da %da paragem a adicionar: ", i+1);

            fflush(stdin);

            fgets(novo->paragens[i].nome, sizeof(novo->paragens[i].nome), stdin);

            novo->paragens[i].nome[strcspn(novo->paragens[i].nome, "\n")] = 0;

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
    else if (cont > totalParagens)
    {
        printf("\n[ERRO] Esta a tentar adicionar mais paragens a linha [%s] do que existem no sistema!", novo->nomeLinha);
        free(novo);
        return head;
    }
    else if (cont < 0){
        printf("\n[ERRO] Esta a inserir um numero negativo. Abortada a criacao...\n");
        free(novo);
        return head;
    }
}

pLinha removeParagemFromLinha(pLinha head, pParagem p, int tam, char* nomeLinha){
    pLinha aux = head;
    int index;

    if (isListEmpty(head) == 1){
        printf("\n[ERRO] Lista vazia.\n");
        return head;
    }

    while(aux != NULL){ // enquanto tiver linhas
        if(strcmp(aux->nomeLinha, nomeLinha) == 0){ // encontra a linha que o user input
            char codigoParagem[MAX];

            printf("\nInsira o codigo da paragem a remover: ");

            scanf(" %s", codigoParagem);

            aux->paragens = removeParagem(aux->paragens, codigoParagem, &aux->nParagens); // atualiza a lista e remove as paragens indicadas pelo user.

            index = checkIfExistsByCode(p, codigoParagem, tam);

            p[index].nLinhas--;

            printf("\n[NOTIFICACAO] Paragem [%s] removida da linha [%s] com sucesso!\n", p[index].nome, aux->nomeLinha);

            return head;
        }
        aux = aux->prox;
    }

    return head;
}

pParagem addParagemToLinha(pParagem p, pLinha head, int tam, char* nomeLinha) {
    char codigoParagem[MAX];
    pLinha aux = head;
    int index;
    pParagem auxP = NULL;
    fflush(stdin);

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

pLinha addParagensToLinhaRefresh(pParagem p, pLinha head, char* nomeLinha, int totalParagens){
    pLinha aux = head;

    if (isListEmpty(head) == 1){
        printf("\n[ERRO] Nao existem linhas no sistema atualmente. Nada a adicionar.\n");
        return head;
    }

    /*if (quant > totalParagens) {
        printf("\n[ERRO] Nao pode adicionar mais paragens a linha do que ja existem.\n");
        return head;
    }*/

    while(aux != NULL){
        if (strcmp(aux->nomeLinha, nomeLinha) == 0){
            aux->paragens = addParagemToLinha(p, aux, totalParagens, nomeLinha);
            //return head;
        }
        aux = aux->prox;
    }

    return head;
}

pLinha removeLinha(pLinha head, pParagem p, int tam){
    pLinha aux = head, anterior;
    char nomeLinha[MAX];

    if(isListEmpty(head) == 1){
        printf("\n[ERRO] Nada a remover. Nao existem linhas no sistema.\n");
        return head;
    }

    printf("\nInsira o nome da linha que deseja remover: ");

    fflush(stdin);

    fgets(nomeLinha, sizeof(nomeLinha), stdin);

    nomeLinha[strcspn(nomeLinha, "\n")] = 0;

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

    decrementaFromSystem(p, head, tam);

    return head; // devolve a lista atualizada
}

void listaAllLinhaInfo(pLinha head){
    pLinha aux = head;

    if (head == NULL) {
        printf("\n[AVISO] Nao existem linhas no sistema atualmente. Experimente criá-las!\n");
        return;
    }

    printf("\nA LISTAR INFO DE TODAS AS LINHAS\n");
    while(aux != NULL){
        if(aux->nParagens > 0) {
            printf("-----------------------------------------------------");
            printf("\nNome da linha: [%s]\n", aux->nomeLinha);
            printf("\nPossui [%d] paragens.\n", aux->nParagens);
            printf("\nAqui estao: \n");
            for (int i = 0; i < aux->nParagens; i++) {
                printf("\nParagem %d: \n", i+1);

                printf("Nome: %s\n", aux->paragens[i].nome);

                printf("Codigo: %s\n", aux->paragens[i].codigo);

                printf("\n");
            }
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
    char userChoice[MAX], codigoParagem[MAX];

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
        listaAllLinhaInfo(head);
    }

    else if (strcmp(userChoice, "paragem") == 0){
        do{
            printf("\nInsira o codigo da paragem a procurar ('fim' para terminar): ");

            fflush(stdin);

            fgets(codigoParagem, sizeof(codigoParagem), stdin);

            codigoParagem[strcspn(codigoParagem, "\n")] = 0;

            listaInfoLinhaByParagem(head, p, totalParagens, codigoParagem);
            //printf("\nTotal: [%d] linhas passam por [%s]\n", numLinhas, nomeParagem); ARRANJAR MANEIRA DE PRINTAR ISTO
            if (strcmp(codigoParagem, "fim") == 0){
                printf("A interromper a listagem...\n");
            }
        }while(strcmp(codigoParagem, "fim") != 0);
    }
}

void listaInfoLinhaByParagem(pLinha head, pParagem p, int totalParagens, char* codigoParagem){
    pLinha aux;

    if(contemParagem(head, codigoParagem) == -1){
        return;
    }

    int index = checkIfExistsByCode(p, codigoParagem, totalParagens); // verifica se essa paragem existe no sistema

    if (index != -1){ // existe no sistema
        printf("\nParagem registada, a mostrar linhas que passam em [%s]...\n", codigoParagem);
        aux = head;
        while(aux != NULL){
            for (int i = 0; i < aux->nParagens; i++){
                if(strcmp(codigoParagem, aux->paragens[i].codigo) == 0) {
                    printf("\nNome linha: [%s]\n", aux->nomeLinha);
                    printf("Numero de paragens: [%d]\n", aux->nParagens);
                }
            }
            aux = aux->prox;
        }
    } else {
        printf("[ERRO] Paragem nao existe no sistema.\n");
        return;
    }
}
