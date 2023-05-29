//
// Created by Gonçalo on 18/04/2023.
//

#ifndef METROMONDEGO_FILES_H
#define METROMONDEGO_FILES_H

#include "paragens.h"
#include "linhas.h"

int findFileSize(char *fileName);
int getNumOfStructsInFile(char *fileName);
void saveInfoLinha(pLinha head, char* fileName); // guarda dentro do ficheiro bin toda a info de linhas + paragens do sistema
pParagem readParagensFromFile(char* fileName, int *total);
void saveInfoParagens(char* fileName, pParagem p, int total);
#endif //METROMONDEGO_FILES_H
