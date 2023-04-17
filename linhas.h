//
// Created by Goncalo on 17/04/2023.
//

#ifndef METROMONDEGO_LINHAS_H
#define METROMONDEGO_LINHAS_H
#include "paragens.h"

typedef struct linhas linha, *pLinha;

struct linhas {
    int nParagens;

    pparagem paragens;
    pLinha prox;
};

#endif //METROMONDEGO_LINHAS_H
