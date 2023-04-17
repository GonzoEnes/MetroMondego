//
// Created by Goncalo on 17/04/2023.
//

#ifndef METROMONDEGO_PARAGENS_H
#define METROMONDEGO_PARAGENS_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

typedef struct paragens paragem, *pparagem;

struct paragens {
    char nome[MAX];
    char codigo[5];
};

pparagem addParagem(pparagem p, int *tam);
pparagem removeParagem(pparagem p, int *tam);
void listaParagem(pparagem p, int tam);

#endif //METROMONDEGO_PARAGENS_H
