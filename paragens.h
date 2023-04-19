//
// Created by Goncalo on 17/04/2023.
//

#ifndef METROMONDEGO_PARAGENS_H
#define METROMONDEGO_PARAGENS_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

typedef struct paragens paragem, *pParagem;

struct paragens {
    char nome[MAX];
    char codigo[5];
};

pParagem addParagem(pParagem p, int *tam);
pParagem removeParagem(pParagem p, int *tam);
void listaParagem(pParagem p, int tam);
int checkIfExistsByCode(pParagem p, char* codigo, int tam);
int checkIfExistsByName(pParagem p, char* nome, int tam);

#endif //METROMONDEGO_PARAGENS_H
