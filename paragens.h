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
    int nLinhas; // a quantas linhas pertence
};

pParagem addParagem(pParagem p, int *tam); // adds paragem to SYSTEM
pParagem removeParagem(pParagem p, int *tam); // remove paragem FROM SYSTEM
void listaParagemSys(pParagem p, int tam); // lista todas as paragens do SISTEMA
//void listaParagemByLinha(pParagem p, int tam, char* nomeLinha);
int checkIfExistsByCode(pParagem p, char *codigo, int tam); // verifica se a paragem existe no sistema pelo codigo dado
int checkIfExistsByName(pParagem p, char *nome, int tam); // verifica se paragem existe no SISTEMA

#endif //METROMONDEGO_PARAGENS_H
