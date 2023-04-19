#include <time.h>
#include "paragens.h"
#include "menu.h"
#include "linhas.h"

int main() {
    pParagem p = NULL; // array dinamico pointer

    pLinha linhas = NULL; // lista ligada pointer

    int tam = 0, n_paragens = 0, totalLinhas = 0;

    srand(time(NULL));

    printf("\nQuantas paragens deseja adicionar? ");

    scanf_s(" %d", &n_paragens);

    printf("Paragens alocadas: %d", n_paragens);

    for (int i = 0; i < n_paragens; i++){
        p = addParagem(p, &tam);
    }

    listaParagemSys(p, tam);

    linhas = criaLinha(linhas, p, tam);

    listaParagemSys(p, tam);

    listaInfoLinha(linhas, p, tam);

    /*do{
        do{
            choice = menu();

            switch(choice){
                case 1:
                    for (int i = 0; i < n_paragens; i++){
                        p = addParagem(p, &tam);
                    }
                    printf("\nLista atualizada: ");
                    listaParagem(p, tam);
                    break;
                case 2:
                    printf("\nInsira o nome da paragem: ");
                    scanf(" %s", nome);
                    p = removeParagem(p, &tam);
                    printf("\nLista atualizada: \n");
                    listaParagem(p, tam);
                    break;
                case 3:
                    listaParagem(p, tam);
                    printf("\nQuantas linhas deseja criar?");
                    scanf_s("%d", &totalLinhas);
                    for (int i = 0; i < totalLinhas; i++){
                        linhas = criaLinha(linhas, p, tam);
                    }
                    //printf("\naqui\n");
                    //listaInfoLinha(linhas, p, totalLinhas);
                    break;
                case 4:
                    printf("A terminar execucao...\n");
                    exit(EXIT_SUCCESS);
                default:
                    printf("\nInsira um input valido!\n");
                    break;
            }
        }while(choice < 1 || choice > 4);
    }while(1);

    free(p);
    freeLinhas(linhas);
    return 0;*/
}
