//
// Created by Goncalo on 17/04/2023.
//
#include "menu.h"

int menu(){
    int opcao;

    printf("\nEscolha a opcao: \n");

    printf("1 - Adicionar uma paragem\n");
    printf("2 - Remover uma paragem\n");
    printf("3 - Listar todas as paragens\n");
    printf("4 - Terminar execucao\n");

    do{
        printf("\nOpcao pretendida: ");
        scanf("%d", &opcao);

        if (opcao < 1 || opcao > 4)
            printf("\nInvalido!");

    }while(opcao < 1 || opcao > 4);

    printf("\n");

    return opcao;
}
