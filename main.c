#include <time.h>
#include "paragens.h"
#include "menu.h"
#include "linhas.h"
#include "files.h"

int main() {
    pParagem p = NULL; // array dinamico pointer

    pLinha linhas = NULL; // lista ligada pointer

    char nomeLinha[MAX];

    char codigo[5];

    char nomeLinhaAux[MAX], nomeParagem[MAX];

    int toAdd, choice, choiceOfUpdate, quantParagens;

    char pontoPartida[MAX], pontoChegada[MAX], updater[MAX];

    int tam = 0, n_paragens = 0, totalLinhas = 0;

    srand(time(NULL));

    linhas = rebuildLinhaFromFile("save.bin");

    if (linhas == NULL) {
        printf("\nFicheiro estava vazio.\nNao acrescentei novas linhas.\n");
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
        do{
            choice = menu();

            switch(choice){
                case 1:
                    p = addParagem(p, &tam);
                    printf("\nLista atualizada, execute o comando de listar informaçao das paragens para ve-la!\n");
                    break;
                case 2:
                    printf("\nInsira o codigo da paragem a remover: ");
                    scanf("%s", codigo);
                    p = removeParagem(p, codigo, &tam);
                    printf("\nLista atualizada, execute o comando de listar informaçao das paragens para ve-la!\n");
                    break;
                case 3:
                    listaParagemSys(p, tam);
                    /*printf("\nQuantas linhas deseja criar?");
                    scanf("%d", &totalLinhas);
                    for (int i = 0; i < totalLinhas; i++){
                        linhas = criaLinha(linhas, p, tam);
                    }*/
                    break;
                case 4:
                    linhas = criaLinha(linhas, p, tam);
                    //printf("\naqui\n");
                    //listaInfoLinha(linhas, p, totalLinhas);
                    break;
                case 5:
                    linhas = removeLinha(linhas);
                    break;
                case 6:
                    listaAllLinhaInfo(linhas, p, tam);
                    break;
                case 7:

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
                    }while(strcmp(pontoPartida, "fim") != 0 || strcmp(pontoChegada, "fim") != 0);

                    break;
                case 8:
                    printf("\nInsira o nome da linha: ");
                    scanf(" %s", updater);
                    printf("\n1 - Remover paragens de linha [%s]\n2 - Adicionar paragens a linha [%s]\nChoice: ", updater, updater);
                    scanf(" %d", &choiceOfUpdate);
                    if (choiceOfUpdate == 1){
                        printf("\nQuantas paragens deseja remover da linha [%s]? ", updater);
                        scanf(" %d", &quantParagens);
                        //linhas = removeParagensFromLinha(linhas, quantParagens, updater);
                    }
                    else if (choiceOfUpdate == 2) {
                        printf("\nQuantas paragens deseja adicionar a linha [%s]? ", updater);
                        scanf(" %d", &quantParagens);
                        linhas = addParagensToLinhaRefresh(p, linhas, quantParagens, updater, tam);
                    }
                    else {
                        printf("\nOpcao invalida!\n");
                        return 0;
                    }
                    break;
                case 9:
                    printf("A terminar execucao...\n");
                    printf("A guardar no ficheiro todas as estruturas antes de terminar...\n");
                    saveInfo(linhas, "save.bin");
                    exit(EXIT_SUCCESS);
                default:
                    printf("\nInsira um input valido!\n");
                    break;
            }
        }while(choice < 1 || choice > 4);
    }while(1);

    free(p);

    freeLinhas(linhas);

    return 0;
}
