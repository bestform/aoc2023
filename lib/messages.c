//
// Created by bestf on 12/26/2023.
//

#include <malloc.h>
#include <string.h>

void makeMessage(const char* name, char** output) {
    char* base = "Hallo, ";

    *output = malloc(strlen(base) + strlen(name) + 1);
    if (*output == NULL) {
        return;
    }
    strcpy(*output, base);
    strcat(*output, name);
}