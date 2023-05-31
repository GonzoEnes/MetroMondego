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
        printf("\n[ERRO] Ficheiro nao tem structs.\n");
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
    pLinha novaLinha = NULL;
    int index;
    char auxParagem[MAX];

    if (f == NULL) {
        printf("\n[ERRO] Nao encontrei ficheiro de texto! [%s]", fileName);
        return head;
    }

    if (fgets(firstLine, sizeof(firstLine), f) != NULL) {

        if (doesLinhaExist(head, firstLine) == 1) {
            printf("\n[ERRO] Linha [%s] ja existe no sistema!\n", firstLine);
            fclose(f);
            return head;
        }

        novaLinha = malloc(sizeof(struct linhas));

        if (novaLinha == NULL) {
            printf("\n[ERRO] Falha na alocacao de espaco para nova linha!\n");
            fclose(f);
            return head;
        }

        firstLine[strcspn(firstLine, "\n")] = 0; // remove o \n da string

        strcpy(novaLinha->nomeLinha, firstLine);

        novaLinha->nParagens = countNumberOfLinesInFileExceptFirst(fileName); // as linhas do ficheiro de texto, excluindo a primeira, vao dar nos o numero completo de paragens que existem no ficheiro

        if (novaLinha->nParagens == 0) {
            printf("\n[ERRO] Nao e possivel criar a linha sem, pelo menos, uma paragem.\n");
            free(novaLinha);
            fclose(f);
            return head;
        }

        novaLinha->paragens = malloc(novaLinha->nParagens * sizeof(struct paragens));

        if (novaLinha->paragens == NULL) {
            printf("\n[ERRO] Falha na alocacao de memoria para paragens da linha [%s]", novaLinha->nomeLinha);
            free(head);
            fclose(f);
            return NULL;
        }

        for (int i = 0; i < novaLinha->nParagens; i++){

            if (fgets(auxParagem, sizeof(auxParagem), f) != NULL) {

                auxParagem[strcspn(auxParagem, "\n")] = 0;

                char* tok = strtok(auxParagem, "#");

                strcpy(novaLinha->paragens[i].nome, tok);

                tok = strtok(NULL, "#");

                strcpy(novaLinha->paragens[i].codigo, tok);

                printf("\nNome Paragem %d: [%s]\n", i+1, novaLinha->paragens[i].nome);

                printf("\nCodigo Paragem %d: [%s]\n", i+1, novaLinha->paragens[i].codigo);

                index = checkIfExistsByCode(p, novaLinha->paragens[i].codigo, tam);

                if (index == -1) {
                    printf("\n[ERRO] Paragem de codigo [%s] nao existe no sistema. Abortada a criacao da linha [%s].\n", novaLinha->paragens[i].codigo, novaLinha->nomeLinha);
                    fclose(f);
                    free(novaLinha->paragens);
                    free(novaLinha);
                    return NULL;
                }

                p[index].nLinhas++;

                novaLinha->paragens[i].nLinhas = p[index].nLinhas;

                novaLinha->prox = NULL;
            }
        }
    }
    else {
        printf("\n[ERRO] Ficheiro vazio. A terminar...\n");
        return NULL;
    }

    head = addToEndOfList(head, novaLinha);

    printf("\n[NOTIFICACAO] Linha [%s] criada com sucesso!\n", novaLinha->nomeLinha);

    fclose(f);

    return head;
}