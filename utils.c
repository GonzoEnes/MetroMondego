//
// Created by Goncalo on 17/04/2023.
//

#include "utils.h"


char* geradorCodigo(){
    int i;
    char *codigo = malloc(sizeof(char) * 5);
    static const char allChars[] = "0123456789"
                                   "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    for (i = 0; i < 4; ++i) {
        codigo[i] = allChars[rand() % (sizeof(allChars) - 1)];
    }

    codigo[4] = '\0';

    return codigo;
}