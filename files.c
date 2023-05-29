//
// Created by Goncalo on 17/04/2023.
//
#include "files.h"

int findFileSize(char* fileName) {
    FILE *f = fopen(fileName, "rt");

    if (f == NULL) {
        return -1;
    }

    fseek(f, 0, SEEK_END);

    int res = ftell(f);

    fclose(f);

    return res;
}

void saveInfoLinha(pLinha head, char* fileName) {
    FILE *f;

    f = fopen(fileName, "wb");

    if (f == NULL) {
        printf("\nErro na criacao do ficheiro [%s]", fileName);
        return;
    }

    while (head != NULL) {
        fwrite(head, sizeof(linha), 1, f);

        for (int i = 0; i < head->nParagens; i++) {
            fwrite(&(head->paragens[i]), sizeof(paragem), 1, f);  // Write each paragem separately
        }
        head = head->prox;
    }

    fclose(f);
}

void saveInfoParagens(char* fileName, pParagem p, int total) {
    FILE *f = fopen(fileName, "wb");

    if (f == NULL) {
        printf("\n[ERRO] Nao consegui abrir %s", fileName);
        return;
    }

    fwrite(p, sizeof(paragem), total, f);
    fclose(f);
}

int getNumOfStructsInFile(char* fileName) {
    FILE *f = fopen(fileName, "rb");
    paragem aux;
    int total = 0;

    if (f == NULL) {
        printf("\n[ERRO] A abrir o ficheiro [%s]", fileName);
        return 0;
    }

    while (fread(&aux, sizeof(paragem), 1, f) == 1) {
        total++;
    }

    fclose(f);
    return total;
}

pParagem readParagensFromFile(char* fileName, int *total) {
    FILE *f = fopen(fileName, "rb");
    pParagem p = NULL;

    *total = getNumOfStructsInFile(fileName);

    if (*total == 0) {
        printf("[ERRO] Ficheiro nao tem structs.\n");
        fclose(f);
        return NULL;
    }

    p = malloc(sizeof(paragem) * (*total));

    if (p == NULL) {
        printf("[ERRO] Falha na alocacao de espaco.\n");
        fclose(f);
        *total = 0;
        return NULL;
    }

    fread(p, sizeof(paragem), *total, f);

    fclose(f);

    return p;
}