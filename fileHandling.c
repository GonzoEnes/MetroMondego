//
// Created by Goncalo on 17/04/2023.
//
#include "fileHandling.h"

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

int countNumberOfLinesInFileExceptFirst(char* fileName) {
    FILE *f = fopen(fileName, "rt");
    int isFirst = 0;
    int totalLines = 0;
    char line[MAX];

    if (f == NULL) {
        printf("\n[ERRO] Falha na abertura de ficheiro [%s]", fileName);
        return -1;
    }

    while (fgets(line, sizeof(line), f) != NULL) {
        if (isFirst == 0) {
            isFirst = 1;
        }
        else {
            totalLines++;
        }
    }

    return totalLines;
}

pLinha createLinhaFromTxtFile(char* fileName, pLinha head, pParagem p, int tam) {
    FILE *f = fopen(fileName, "rt");
    char firstLine[MAX];

    if (f == NULL) {
       printf("\n[ERRO] Nao encontrei ficheiro de texto! [%s]", fileName);
       return NULL;
    }

    if (fgets(firstLine, sizeof(firstLine), f) != NULL) {

        head = malloc(sizeof(struct linhas));

        if (head == NULL) {
            printf("\n[ERRO] Falha na alocacao de espaco para nova linha!\n");
            fclose(f);
            return NULL;
        }

        firstLine[strcspn(firstLine, "\n")] = 0; // remove o \n da string

        strcpy(head->nomeLinha, firstLine);

        head->nParagens = countNumberOfLinesInFileExceptFirst(fileName);

        if (head->nParagens == 0) {
            printf("\n[ERRO] Nao e possivel criar a linha sem, pelo menos, uma paragem.\n");
            free(head);
            fclose(f);
            return NULL;
        }

        head->paragens = malloc(head->nParagens * sizeof(struct paragens));

        if (head->paragens == NULL) {
            printf("\n[ERRO] Falha na alocacao de memoria para paragens da linha [%s]", head->nomeLinha);
            free(head);
            fclose(f);
            return NULL;
        }

        // continuar amanhã
        // read again to catch paragens

        for (int i = 0; i < head->nParagens; i++){
            if (fgets(head->paragens[i].nome, sizeof(head->paragens[i].nome), f) != NULL) {

                head->paragens[i].nome[strcspn(head->paragens[i].nome, "#")] = 0;

                int index = checkIfExistsByName(p, head->paragens[i].nome, tam);

                if (index == -1) {
                    printf("\n[ERRO] Paragem [%s] nao existe no sistema. Abortada a criacao da linha [%s].\n", head->paragens[i].nome, head->nomeLinha);
                    fclose(f);
                    free(head->paragens);
                    free(head);
                    return NULL;
                }

                p[index].nLinhas++;

                head->paragens[i].nLinhas = p[index].nLinhas;

                /*if (fgets(head->paragens[i].codigo, sizeof(head->paragens[i].codigo), f) != NULL) {
                    printf("\nLinha [%s] lida com sucesso do ficheiro [%s]! Consulte as linhas para mais informacao.\n", head->nomeLinha, fileName);
                    return head;
                }*/

                //head->paragens[i].codigo[strcspn(head->paragens[i].codigo, "\n")] = 0;

                // dar fix agora ao codigo da paragem,ler dpois do delimitador

                printf("\n[ERRO] Ficheiro mal formatado. Nao existem paragens.\n");
            }
        }
    }
    else {
        printf("\n[ERRO] Ficheiro vazio. A terminar...\n");
        return NULL;
    }

    fclose(f);
    return head;
}