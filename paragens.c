//
// Created by Goncalo on 17/04/2023.
//

#include "paragens.h"
#include "utils.h"

pparagem addParagem(pparagem p, int *tam){

    paragem novo;

    pparagem aux = realloc(p, sizeof(struct paragens) * (*tam + 1));

    if (aux == NULL){
        printf("\nErro na alocacao de memoria das paragens.\n");
        return p;
    }

    printf("\nIntroduza o nome da paragem: ");
    scanf(" %s", novo.nome);

    for (int i = 0; i < *tam; i++){
        if(strcmp(aux[i].nome, novo.nome) == 0){
            printf("\nParagem [%s] ja existe no sistema.\n", novo.nome);
            return aux;
        }
    }

    //strcpy(novo.codigo,geradorCodigo());

    strcpy(novo.codigo, geradorCodigo());

    printf("\nA atribuir o codigo... [%s]", novo.codigo);

    aux[(*tam)] = novo;

    (*tam)++;

    return aux;
}

pparagem removeParagem(pparagem p, int *tam){

    pparagem aux = NULL;

    paragem retorna;

    int index = 0;

    char nome[MAX];

    printf("\nInsira o codigo da paragem a remover: ");

    scanf(" %s", nome);

    for (int i = 0; i < *tam; i++){
        if (strcmp(p[i].nome, nome) == 0){
            printf("\nA remover da lista... [%s]", p[i].nome);
            index = i;
            break;
        }
    }

    retorna = p[index]; // guardar caso a realloc corra mal

    p[index] = p[(*tam)-1];

    (*tam)--;

    aux = realloc(p, (*tam) * sizeof(paragem));

    if (aux == NULL){

        printf("\nErro na alocacao de memoria ao remover.\n");

        p[index] = retorna;

        return p;
    }

    return aux;
}

void listaParagem(pparagem p, int tam){
    printf("\n------------ A LISTAR PARAGENS ------------\n");

    for (int i = 0; i < tam; i++){
        printf("\nParagem %d: \n", i+1);

        printf("Nome: %s\n", p[i].nome);

        printf("Codigo: %s\n", p[i].codigo);
    }

    printf("\n------------ FIM ------------\n");
}


