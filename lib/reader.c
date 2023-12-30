//
// Created by bestf on 12/27/2023.
//

#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "reader.h"

fileContents linesOfFile(const char* path) {
    int lines_allocated = 100;
    int step_size = 100;

    char** contents = malloc(lines_allocated * sizeof(char*));

    FILE* fp2;
    fp2 = fopen(path, "r");
    if (fp2 == NULL) {
        printf("Could not reopen file %s", path);
        exit(EXIT_FAILURE);
    }

    int i = 0;
    int chunk_size = 250;
    char buffer[chunk_size];
    while (fgets(buffer, chunk_size, fp2)) {
        if (i >= lines_allocated) {
            lines_allocated += step_size;
            char** new_contents = realloc(contents, (sizeof *contents) * lines_allocated);
            if (contents == NULL) {
                printf("Failed to reallocate memory for a string");
                exit(EXIT_FAILURE);
            }
            contents = new_contents;
        }
        contents[i] = strdup(buffer);
        if (contents[i] == NULL) {
            printf("Failed to allocate memory for a string");
            exit(EXIT_FAILURE);
        }
        i++;
    }
    fclose(fp2);

    fileContents r = {
        lines: contents,
        len: i,
    };

    return r;
}

void freeFileContents(fileContents* contents) {
    for (int i = 0; i < contents->len; i++) {
        free(contents->lines[i]);
    }
}