#include <time.h>
#include "paragens.h"
#include "menu.h"
#include "linhas.h"
#include "fileHandling.h"

int main() {
    pParagem p = NULL; // array dinamico pointer

    pLinha linhas = NULL; // lista ligada pointer

    char nomeLinha[MAX];

    char codigo[5];

    char nomeLinhaAux[MAX], nomeParagem[MAX];

    int toAdd, choice, choiceOfUpdate, quantParagens;

    char pontoPartida[MAX], pontoChegada[MAX], updater[MAX], nomeFich[MAX];

    int tam = 0, n_paragens = 0, totalLinhas = 0;

    setbuf(stdout, NULL);

    srand(time(NULL));

    printf("--------------BEM VINDO AO SISTEMA METRO MONDEGO! --------------\n");

    linhas = rebuildLinhaFromFile("saveLinhas.bin");

    p = readParagensFromFile("saveParagens.bin", &tam);

    if (p == NULL) {
        printf("\n[AVISO] Ficheiro de paragens esta vazio. Nao acrescentei novas paragens.\n");
    }
    else {
        printf("\n[NOTIFICACAO] Ficheiro detetado. A reconstruir paragens de ficheiro binario...\n");
    }
    if (linhas == NULL) {
        printf("\n[AVISO] Ficheiro de linhas estava vazio.\nNao acrescentei novas linhas.\n");
    }
    else {
        printf("\n[NOTIFICACAO] Ficheiro detetado. A reconstruir linhas de ficheiro binario...\n");
    }

    /*
    printf("Paragens alocadas: %d", n_paragens);

    for (int i = 0; i < n_paragens; i++){
        p = addParagem(p, &tam);
    }

    listaParagemSys(p, tam);

    removeParagem(p, &tam);

    listaParagemSys(p, tam);

    removeParagem(p, &tam);

    listaParagemSys(p, tam);

    linhas = criaLinha(linhas, p, tam);

    printf("\nQuantas paragens quer adicionar?");

    scanf("%d", &toAdd);

    printf("\nNome linha a que quer add paragens: ");
    scanf("%s", nomeLinhaAux);

    linhas = addParagensToLinha(linhas, toAdd, nomeLinhaAux);

    listaParagemSys(p, tam);

    if(linhas == NULL){
        return 0;
    }

    listaInfoLinha(linhas, p, tam);

    /*printf("\nQue linha deseja remover as paragens?");
    scanf(" %s", nomeLinha);

    int quantas = 0;

    printf("\nQuantas paragens deseja remover?\n");
    scanf(" %d", &quantas);

    // linhas = removeParagensFromLinha(linhas, quantas, nomeLinha);

    // listaInfoLinha(linhas, p, tam);

    printf("\nInsira o ponto de partida e ponto de chegada para o seu percurso: ");

    do {

        printf("\nPonto partida: ('fim' para acabar)");
        scanf(" %s", pontoPartida);
        printf("\nInseriu: %s", pontoPartida);


        printf("\nPonto chegada: ('fim' para acabar)");
        scanf(" %s", pontoChegada);
        printf("\nInseriu: %s", pontoChegada);

        calculaParagensSemOverflow(linhas, pontoPartida, pontoChegada);

        if(strcmp(pontoPartida, "fim") == 0 && strcmp(pontoChegada, "fim") == 0){
            printf("\nA terminar...\n");
        }

    }while(strcmp(pontoPartida, "fim") != 0 && strcmp(pontoChegada, "fim") != 0);

    printf("\nInsira o nome da linha que quer retirar paragens: ");
    scanf("%s", nomeLinha);

    printf("\nInsira quantas paragens quer remover ");
    scanf(" %d", &n_paragens);

    linhas = removeParagensFromLinha(linhas, n_paragens, nomeLinha);

    listaInfoLinha(linhas, p, totalLinhas);

    linhas = removeLinha(linhas);

    freeLinhas(linhas);*/

    do{
        choice = menu();

        switch(choice){
            case 1:
                printf("\nQuantas paragens quer adicionar?\n");

                scanf(" %d", &n_paragens);

                for (int i = 0; i < n_paragens; i++) {
                    p = addParagem(p, &tam);
                }

                printf("\nLista atualizada, execute o comando de listar informacao das paragens para ve-la!\n");

                break;
            case 2:
                printf("\nInsira o codigo da paragem a remover: ");
                scanf("%s", codigo);
                p = removeParagem(p, codigo, &tam);
                printf("\nLista atualizada, execute o comando de listar informacao das paragens para ve-la!\n");
                break;
            case 3:
                listaParagemSys(p, tam);
                break;
            case 4:
                linhas = criaLinha(linhas, p, tam);
                break;
            case 5:
                linhas = removeLinha(linhas, p, tam);
                break;
            case 6:
                listaAllLinhaInfo(linhas);
                break;
            case 7:
                do {
                    fflush(stdin);

                    printf("\nPonto partida ('fim' para acabar): ");

                    fgets(pontoPartida, sizeof(pontoPartida), stdin);

                    pontoPartida[strcspn(pontoPartida, "\n")] = 0;

                    printf("\nPonto chegada ('fim' para acabar): ");

                    fgets(pontoChegada, sizeof(pontoChegada), stdin);

                    pontoChegada[strcspn(pontoChegada, "\n")] = 0;

                    calculaParagensSemOverflow(linhas, pontoPartida, pontoChegada);

                    if(strcmp(pontoPartida, "fim") == 0 && strcmp(pontoChegada, "fim") == 0){
                        printf("\nA terminar...\n");
                    }
                }while(strcmp(pontoPartida, "fim") != 0 || strcmp(pontoChegada, "fim") != 0);
                break;
            case 8:
                printf("\nInsira o nome da linha: ");

                fflush(stdin);

                fgets(updater, sizeof(updater), stdin);

                updater[strcspn(updater, "\n")] = 0;

                if (doesLinhaExist(linhas, updater) != 1) {
                    printf("\n[ERRO] Nome da linha nao encontrado no sistema.\n");
                    break;
                }

                printf("\n1 - Remover paragem de linha [%s]\n2 - Adicionar paragem a linha [%s]\nChoice: ", updater, updater);

                scanf(" %d", &choiceOfUpdate);

                if (choiceOfUpdate == 1){
                    linhas = removeParagemFromLinha(linhas, p, tam, updater);
                    printf("\n[NOTIFICACAO] Paragem removida com sucesso!\n");
                }
                else if (choiceOfUpdate == 2) {
                    linhas = addParagensToLinhaRefresh(p, linhas, updater, tam);
                    printf("\n[NOTIFICACAO] Paragem adicionada com sucesso!\n");
                }
                else {
                    printf("\nOpcao invalida!\n");
                    break;
                }
                break;
            case 9:
                printf("\nInsira o nome do ficheiro de texto (com .txt apos o nome):  ");
                scanf(" %s", nomeFich);
                linhas = createLinhaFromTxtFile(nomeFich, linhas, p, tam);
                break;
            case 0:
                printf("A terminar execucao...\n");
                printf("A guardar no ficheiro todas as estruturas antes de terminar...\n");
                saveInfoLinha(linhas, "saveLinhas.bin");
                saveInfoParagens("saveParagens.bin", p, tam);
                break;
            default:
                printf("\nInsira um input valido!\n");
                break;
        }

    }while(choice != 0);

    free(p); // libertar o espaço das paragens

    freeLinhas(linhas); // libertar o espaço das linhas

    printf("\n-------------- FIM PROGRAMA METRO MONDEGO! OBRIGADO! --------------\n");

    return 0;
}