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

int contemParagem(pLinha head, pParagem p, char* nomeParagem){
    while(head != NULL){
        for (int i = 0; i < head->nParagens; i++){
            if(strcmp(head->paragens[i].nome, nomeParagem) == 0){
                return 1;
            }
        }

        head = head->prox;
    }
    return 0;
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

    scanf_s(" %s", novo->nomeLinha, MAX);

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
            scanf_s(" %s", nomeParagem, MAX);

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

pLinha updateLinha(pLinha head, pParagem p, int total){
    printf("\nQue operacao deseja realizar? Inserir uma das tres opcoes: \n");
    printf("'remove' 'adicionar' ''");

    return head;
}

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
        scanf_s(" %s", userChoice, MAX);

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
            scanf_s(" %s", nomeParagem, MAX);

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


