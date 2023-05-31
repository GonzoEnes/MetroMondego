//
// Created by Goncalo on 17/04/2023.
//

#ifndef METROMONDEGO_LINHAS_H
#define METROMONDEGO_LINHAS_H
#include "paragens.h"

typedef struct linhas linha, *pLinha;

struct linhas {
    int nParagens;
    char nomeLinha[MAX];
    pParagem paragens;
    pLinha prox;
};

void freeLinhas(pLinha linhas);
void decrementaFromSystem(pParagem p, pLinha head, int totalParagens);
pLinha criaLinha(pLinha head, pParagem p, int totalParagens);
pLinha removeLinha(pLinha head, pParagem p, int tam);
pLinha removeParagemFromLinha(pLinha head, pParagem p, int tam, char* nomeLinha); // remove X paragens de linha Y
int isListEmpty(pLinha linhas);
void listaInfoLinha(pLinha head, pParagem p, int totalLinhas);
void listaInfoLinhaByParagem(pLinha head, pParagem p, int totalLinhas, char nomeParagem[MAX]);
int contemParagem(pLinha head, char* codigoParagem); // verifica se contem uma determinada paragem passada por parametro na lista de linhas
int doesLinhaExist(pLinha head, char* nomeLinha);
void calculaParagensSemOverflow(pLinha head, char* nomePartida, char* nomeDestino);
void listaAllLinhaInfo(pLinha head);
pParagem addParagemToLinha(pParagem p, pLinha head, int tam, char* nomeLinha);
pLinha addParagensToLinhaRefresh(pParagem p, pLinha head, char* nomeLinha, int totalParagens); // se possível, mudar tudo para algo assim, fica mais giro // adiciona X paragens a linha Y
pLinha rebuildLinhaFromFile(char* fileName);
pLinha addToEndOfList(pLinha head, pLinha novoNo);
void incrementaAfterAdding(pLinha head, char* nomeLinha); // incrementa o n linhas para quando uma paragem sai de uma linha ou entra (atualiza o valor nas outras linhas)
void decrementaAfterRemoving(pLinha head, char* nomeLinha);

#endif //METROMONDEGO_LINHAS_H