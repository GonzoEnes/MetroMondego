//
// Created by Goncalo on 17/04/2023.
//

#ifndef METROMONDEGO_LINHAS_H
#define METROMONDEGO_LINHAS_H
#include "paragens.h"

typedef struct linhas linha, *pLinha;

struct linhas {
    int nParagens;
    int nLinhas;
    char nomeLinha[MAX];
    pparagem paragens;
    pLinha prox;
};

void freeLinhas(pLinha linhas);
pLinha criaLinha(pLinha head, pparagem p, int total);
pLinha addParagemToList(pLinha head, pparagem p, int quantas);
int isListEmpty(pLinha linhas);
void listaInfoList(pLinha head);

#endif //METROMONDEGO_LINHAS_H
