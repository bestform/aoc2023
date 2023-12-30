//
// Created by bestf on 12/27/2023.
//

#ifndef AOC2023_READER_H
#define AOC2023_READER_H

typedef struct {
    char** lines;
    int len;
} fileContents;

fileContents linesOfFile(const char* path);

void freeFileContents(fileContents* contents);

#endif //AOC2023_READER_H
