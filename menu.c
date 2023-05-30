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
    printf("4 - Adicionar uma linha\n");
    printf("5 - Remover uma linha\n");
    printf("6 - Listar todas as linhas\n");
    printf("7 - Calcule um percurso entre dois pontos\n");
    printf("8 - Atualizar informacao de uma linha\n");
    printf("9 - Criar uma linha de um ficheiro de texto\n");
    printf("10 - Terminar execucao");

    do{
        printf("\nOpcao pretendida: ");
        scanf("%d", &opcao);

        if (opcao < 1 || opcao > 10)
            printf("\nInput invalido!");

    }while(opcao < 1 || opcao > 10);

    printf("\n");

    return opcao;
}
