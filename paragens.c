//
// Created by Goncalo on 17/04/2023.
//

#include "utils.h"
#include "linhas.h"

pParagem addParagem(pParagem p, int *tam){

    paragem novo;

    printf("\nIntroduza o nome da paragem: ");

    fflush(stdin);

    fgets(novo.nome, sizeof(novo.nome), stdin);

    novo.nome[strcspn(novo.nome, "\n")] = 0;

    int index = checkIfExistsByName(p, novo.nome, *tam);

    if (index != -1) {
        printf("\n[ERRO] Nao consigo adicionar uma paragem que ja existe! [%s]", novo.nome);
        return p;
    }

    pParagem aux = realloc(p, sizeof(struct paragens) * (*tam + 1));

    if (aux == NULL){
        printf("\nErro na alocacao de memoria das paragens.\n");
        return p;
    }

    strcpy(novo.codigo, geradorCodigo());

    novo.nLinhas = 0; // inicialmente não pertence a nenhuma linha

    printf("\n[NOTIFICACAO] A atribuir o codigo... [%s]", novo.codigo);

    aux[(*tam)] = novo;

    (*tam)++;

    return aux;
}

pParagem removeParagem(pParagem p, char* codigo, int *tam){

    pParagem aux = NULL;

    paragem retorna;

    int index;

    index = checkIfExistsByCode(p, codigo, *tam);

    printf("\n[%s]", p[index].nome);

    if (index != -1) {

        retorna = p[index]; // guardar caso a realloc corra mal

        p[index] = p[(*tam)-1];

        (*tam)--;
    }
    else {
        printf("\n[ERRO] Nao consigo remover uma paragem que nao existe!");
        return p;
    }

    if (*tam == 0) {
        free(p);
        return NULL;
    }

    aux = realloc(p, (*tam) * sizeof(paragem));

    if (aux == NULL){

        printf("\n[ERRO] Alocacao de memoria ao remover.\n");

        p[index] = retorna;

        return p;
    }
    return aux;
}

int checkIfExistsByCode(pParagem p, char *codigo, int tam){
    for (int i = 0; i < tam; i++){
        if(strcmp(p[i].codigo, codigo) == 0){
            return i; //retorna o indice onde esta a paragem no array
        }
    }
    return -1;
}

int checkIfExistsByName(pParagem p, char* nome, int tam){
    for (int i = 0; i < tam; i++){
        if(strcmp(p[i].nome, nome) == 0){
            return i; //retorna o indice onde esta a paragem no array
        }
    }
    return -1;
}

void listaParagemSys(pParagem p, int tam){
    if(tam == 0){
        printf("\n[WARNING] Nada a listar. Nao existem paragens no sistema.\n");
        return;
    }

    printf("\n------------ A LISTAR PARAGENS ------------\n");

    for (int i = 0; i < tam; i++){
        printf("\nParagem %d: \n", i+1);

        printf("Nome: %s\n", p[i].nome);

        printf("Codigo: %s\n", p[i].codigo);

        printf("\nPertence a: %d linhas\n", p[i].nLinhas);
    }

    printf("\n------------  FIM DA LISTAGEM  ------------\n");
}
