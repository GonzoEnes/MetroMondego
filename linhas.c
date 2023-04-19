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

void listaLinhas(pLinha head){
    if (isListEmpty(head) == 1){
        return;
    }

    printf("\n A LISTAR INFO SOBRE LINHAS METRO MONDEGO: ");

    while(head != NULL){
        printf("\nLinha contem %d paragens.\n", head->nParagens); // ir adicionando mais info

        head = head->prox;
    }
}

pLinha addParagemToList(pLinha head, pparagem p, int quantas){

    return head;
}

pLinha criaLinha(pLinha head, pparagem p, int total){
    pLinha novo, aux;
    int nParagens;

    novo = malloc(sizeof(linha));

    if (novo == NULL){
        printf("\n[ERRO] Alocacao de memoria para nova linha!\n");
        return head;
    }

    aux = head;

    printf("\nQual o nome da linha?\n");

    scanf(" %s", novo->nomeLinha);

    while (aux != NULL){
        if(strcmp(aux->nomeLinha, novo->nomeLinha) == 0){ // se ja existir essa

            printf("\n[ERRO] Nao foi possivel adicionar essa linha. Ja existe no sistema.\n");

            return aux;
        }

        aux = aux->prox;
    }

    printf("\nQuantas paragens deseja adicionar?\n");
    scanf(" %d", &novo->nParagens);

    nParagens = novo->nParagens; // atribuir para o contador dentro do scope para nao alterar o da func

    // acabar

    novo->paragens = p;

    return head;
}


