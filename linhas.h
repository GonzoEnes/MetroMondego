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
    pParagem paragens;
    pLinha prox;
};

void freeLinhas(pLinha linhas);
pLinha criaLinha(pLinha head, pParagem p, int total);
int isListEmpty(pLinha linhas);
void listaInfoLinha(pLinha head);

#endif //METROMONDEGO_LINHAS_H
