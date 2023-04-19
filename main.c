#include <time.h>
#include "paragens.h"
#include "menu.h"
#include "linhas.h"

int main() {
    pParagem p = NULL;

    pLinha linhas = NULL;

    int tam = 0, choice, n_paragens = 0;

    char nome[MAX];

    srand(time(NULL));

    printf("\nQuantas paragens deseja adicionar? ");

    scanf(" %d", &n_paragens);

    printf("Paragens alocadas: %d", n_paragens);

    while(1){
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
                    linhas = criaLinha(linhas, p, tam);
                    listaInfoLinha(linhas);
                    break;
                case 4:
                    printf("A terminar execucao...\n");
                    exit(EXIT_SUCCESS);
                default:
                    break;
            }
        }while(choice < 1 || choice > 4);
    }

    free(p);
    return 0;
}
