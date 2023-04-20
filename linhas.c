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

pLinha contemParagem(pLinha head, char* nomeParagem){
    pLinha aux = head;
    while(aux != NULL){
        for (int i = 0; i < aux->nParagens; i++){
            if(strcmp(aux->paragens[i].nome, nomeParagem) == 0){
                return head;
            }
        }
        aux = aux->prox;
    }
    return NULL;
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

pLinha criaLinha(pLinha head, pParagem p, int totalParagens){

    pLinha novo, aux = NULL;
    paragem novaParagem;
    int cont = 0;
    char nomeParagem[MAX];

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
        printf("\n[WARNING] Nao existem paragens no sistema. Criada linha sem lista de paragens. Atualize a linha depois para lhe adicionar paragens.\n");
        novo->prox = NULL;
        aux = head;
        while(aux->prox != NULL){
            aux = aux->prox;
        }
        aux->prox = novo;
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
            scanf(" %s", nomeParagem);

            if(strcmp(novo->paragens[i].nome, nomeParagem) == 0){ // verificar se essa paragem já foi adicionada aquando a criação DAR DEBUG
                printf("\n[ERRO] Esta paragem ja se encontra na linha!\n");
                break;
            }

            int index = checkIfExistsByName(p, nomeParagem, totalParagens); // verifica se existe essa paragem no sistema

            if (index != -1){
                p[index].nLinhas++;

                novaParagem = p[index]; // vai buscar essa paragem ao indice de onde a encontrou no sistema

                novo->paragens[i] = novaParagem;

                printf("\n[SUCESSO] Paragem [%s] adicionada a linha [%s]!\n", novaParagem.nome, novo->nomeLinha);
            }
            else {
                printf("\n[ERRO] Esta a tentar adicionar uma paragem que nao existe no sistema ainda! Experimente cria-la!\n");
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

pLinha removeParagensFromLinha(pLinha head, int quant, char* nomeLinha){
    pLinha aux = head;

    if (isListEmpty(head) == 1){
        printf("\n[ERRO] Lista vazia.\n");
        return head;
    }

    while(aux != NULL){ // enquanto tiver linhas
        if(strcmp(aux->nomeLinha, nomeLinha) == 0){ // encontra a linha que o user input
            while(aux->nParagens >= quant && quant > 0){ // enquanto a quantidade que o user inseriu for menor que o numero total de paragens e maior que 0
                aux->paragens = removeParagem(aux->paragens, &aux->nParagens); // atualiza a lista e remove as paragens indicadas pelo user.
                quant--; // reduz o cont
            }
        }
        aux = aux->prox;
    }

    return head;
}

pLinha addParagensToLinha(pLinha head, int quant, char* nomeLinha){
    pLinha aux = head;

    if (isListEmpty(head) == 1){
        printf("\n[ERRO] Nao existem linhas no sistema atualmente. Nada a adicionar.\n");
        return head;
    }

    while(aux != NULL){
        if (strcmp(aux->nomeLinha, nomeLinha) == 0){
            // TODO
        }
        aux = aux->prox;
    }

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
    return head; // devolve a lista atualizada
}

    /* METER ESTE CODIGO NA MAIN DEPOIS QUANDO FIZER A UI
     * printf("\nQue operacao deseja realizar? Inserir uma das duas opcoes: 'remover' ou 'adicionar'\n");

    do{
        scanf(" %s", userInput);

        if (strcmp(userInput, "remover") != 0 && strcmp(userInput, "atualizar") != 0 && strcmp(userInput, "adicionar") != 0){
            printf("\n[ERRO] Formato invalido. Insira 'remover' ou 'adicionar'");
        }
    }while(strcmp(userInput, "remover") != 0 && strcmp(userInput, "adicionar") != 0);*/

void listaInfoLinha(pLinha head, pParagem p, int totalParagens){ //dividir melhor esta função para não ficar tão grande quando tiver tempo
    pLinha aux;
    char userChoice[MAX], nomeParagem[MAX];

    int index, numLinhas = 0;

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
        printf("\nA LISTAR INFO DE TODAS AS LINHAS\n");
        aux = head;
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

    else if (strcmp(userChoice, "paragem") == 0){
        do{
            printf("\nInsira o nome da paragem ('fim' para parar a listagem): ");
            scanf(" %s", nomeParagem);

            printf("\nINSERIU: %s\n", nomeParagem);

            index = checkIfExistsByName(p, nomeParagem, totalParagens); // verifica se essa paragem existe no sistema

            if (index != -1){ // existe no sistema
                printf("\nParagem registada, a mostrar linhas que passam em [%s]...\n", nomeParagem);
                aux = head;
                while(aux != NULL){
                    for (int i = 0; i < aux->nParagens; i++){
                        if(strcmp(nomeParagem, aux->paragens[i].nome) == 0){
                            printf("\nNome linha: %s\n", aux->nomeLinha);
                            printf("Numero de paragens: [%d]\n", aux->nParagens);
                            numLinhas++;
                        }
                    }
                    aux = aux->prox;
                }
                printf("\nTotal: [%d] linhas passam por [%s]\n", numLinhas, nomeParagem);
            }
            else if (strcmp(nomeParagem, "fim") == 0){
                printf("A interromper a listagem...\n");
            }
            else {
                printf("[ERRO] Paragem nao existe no sistema.\n");
            }
        }while(strcmp(nomeParagem, "fim") != 0);
    }
}


