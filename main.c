#include <stdio.h>
#include <malloc.h>
#include "lib/01.h"
#include "lib/reader.h"

void solve01() {
    fileContents contents = linesOfFile("data/01.txt");

    int total = 0;

    for (int i = 0; i < contents.len; i++) {
        int num = intForLine(contents.lines[i]);
        total += num;
    }

    printf("%i", total);
}

void solve01b() {
    fileContents contents = linesOfFile("data/01.txt");

    int total = 0;

    for (int i = 0; i < contents.len; i++) {
        int num = intForLineB(contents.lines[i]);
        total += num;
    }

    printf("%i", total);
}

int main() {
    solve01b();

    return 0;
}


