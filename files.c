//
// Created by Goncalo on 17/04/2023.
//
#include "files.h"

int findFileSize(char* fileName){
    FILE *f = fopen(fileName, "rt");

    if(f == NULL){
        return -1;
    }

    fseek(f, 0, SEEK_END);

    int res = ftell(f);

    fclose(f);

    return res;
}




