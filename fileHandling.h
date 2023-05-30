//
// Created by Gonçalo on 18/04/2023.
//

#ifndef METROMONDEGO_FILEHANDLING_H
#define METROMONDEGO_FILEHANDLING_H

#include "paragens.h"
#include "linhas.h"

int findFileSize(char *fileName);
int getNumOfStructsInFile(char *fileName);
void saveInfoLinha(pLinha head, char* fileName); // guarda dentro do ficheiro bin toda a info de linhas + paragens do sistema
pParagem readParagensFromFile(char* fileName, int *total);
void saveInfoParagens(char* fileName, pParagem p, int total);
pLinha createLinhaFromTxtFile(char* fileName, pLinha head);
int countNumberOfLinesInFileExceptFirst(char *fileName);

#endif //METROMONDEGO_FILEHANDLING_H
