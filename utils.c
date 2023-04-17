//
// Created by Goncalo on 17/04/2023.
//

#include "utils.h"


char* geradorCodigo(){
    int i;
    char *code = malloc(sizeof(char) * 5);
    static const char alphanum[] = "0123456789"
                                   "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    for (i = 0; i < 4; ++i) {
        code[i] = alphanum[rand() % (sizeof(alphanum) - 1)];
    }

    code[4] = '\0';

    return code;
}