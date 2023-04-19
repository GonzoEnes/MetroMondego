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
pLinha criaLinha(pLinha head, pParagem p, int totalParagens);
pLinha removeLinha(pLinha head);
pLinha removeParagensFromLinha(pLinha head, int quant, char* nomeLinha);
pLinha updateLinha(pLinha head, int quantRemover, char* nomeLinha);
int isListEmpty(pLinha linhas);
void listaInfoLinha(pLinha head, pParagem p, int totalLinhas);
pLinha contemParagem(pLinha head, char* nomeParagem); // verifica se contem uma determinada paragem passada por parametro na lista de linhas
int doesLinhaExist(pLinha head, char* nomeLinha);

#endif //METROMONDEGO_LINHAS_H
