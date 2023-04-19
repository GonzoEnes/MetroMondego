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

pLinha criaLinha(pLinha head, pParagem p, int totalParagens){
    pLinha novo, aux = head;
    paragem novaParagem;
    int cont = 0;
    char nomeParagem[MAX];

    novo = malloc(sizeof(linha));

    if (novo == NULL){
        printf("\n[ERRO] Alocacao de memoria para nova linha!\n");
        return head;
    }

    printf("\nQual o nome da linha? \n");

    scanf_s(" %s", novo->nomeLinha);

    while (aux != NULL){
        if(strcmp(aux->nomeLinha, novo->nomeLinha) == 0){ // se ja existir essa
            printf("\n[ERRO] Nao foi possivel adicionar linha [%s]. Ja existe no sistema.\n", novo->nomeLinha);
            free(novo);
            return aux;
        }
        aux = aux->prox;
    }

    if (totalParagens == 0){
        printf("\n[WARNING] Nao existem paragens no sistema. Criada linha sem lista de paragens.\n");
        return novo;
    }

    printf("\nQuantas paragens deseja adicionar? Existem %d paragens no sistema.\n", totalParagens);
    scanf_s(" %d", &cont);

    if(cont <= totalParagens){
        novo->nParagens = cont;

        novo->paragens = malloc(novo->nParagens * sizeof(paragem)); // aloca espaço para as paragens dessa linha

        if(novo->paragens == NULL){
            printf("\n[ERRO] Alocacao de espaco para as paragens da linha [%s]\n", novo->nomeLinha);
            free(novo);
            return head;
        }

        for (int i = 0; i < novo->nParagens; i++){
            printf("\nInsira o nome da %da paragem a adicionar: ", i+1);

            scanf_s(" %s", nomeParagem);

            int index = checkIfExistsByName(p, nomeParagem, totalParagens); // verifica se existe essa paragem no sistema

            if (index != -1){
                novaParagem = p[index]; // vai buscar essa paragem ao indice de onde a encontrou no sistema

                novo->paragens[i] = novaParagem;
                //printf("\nInfo paragem: %s %s", novo->paragens[i].nome, novo->paragens[i].codigo);
                /*while (cont < novo->nParagens){
                    novo->paragens[cont] = novaParagem;
                    cont++;
                }*/

                printf("\n[SUCESSO] Paragem [%s] adicionada a linha [%s]!\n", novaParagem.nome, novo->nomeLinha);
            }
            else {
                printf("\n[ERRO] Esta a tentar adicionar uma paragem que nao existe no sistema ainda! Experimente cria-la!\n");
                free(novo);
                return head;
            }
        }
    }
    else
    {
        printf("\n[ERRO] Esta a tentar adicionar mais paragens a linha [%s] do que existem no sistema!", novo->nomeLinha);
        free(novo);
        return head;
    }
    return novo;
}

void listaInfoLinha(pLinha head){


    if (isListEmpty(head) == 1){
        printf("[WARNING] Nada a listar. Nao existem linhas no sistema. Experimente cria-las!");
        return;
    }

    printf("\nA LISTAR INFO SOBRE LINHA [%s]\n", head->nomeLinha);

    while(head != NULL){
        printf("\nNome da linha: [%s]", head->nomeLinha);

        printf("\nPossui [%d] paragens.\n", head->nParagens);

        printf("\nAqui estao: ");

        listaParagem(head->paragens, head->nParagens);

        head = head->prox;
    }
}


