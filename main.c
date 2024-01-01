#include <stdio.h>
#include <malloc.h>
#include "lib/01.h"
#include "lib/02.h"
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

void solve02() {
    fileContents contents = linesOfFile("data/02.txt");

    int total = 0;

    for (int i = 0; i < contents.len; i++) {
        Game* game = game_for_line(contents.lines[i]);
        Round max = max_throws_for_game(game);
        if (max.reds <= 12 && max.greens <= 13 && max.blues <= 14) {
            int id = atoi(game->id);
            total += id;
        }
        free(game);
    }

    printf("%i", total);
}

void solve02b() {
    fileContents contents = linesOfFile("data/02.txt");

    int total = 0;

    for (int i = 0; i < contents.len; i++) {
        Game* game = game_for_line(contents.lines[i]);
        Round max = max_throws_for_game(game);
        int power = max.blues * max.greens * max.reds;
        total += power;
        free(game);
    }

    printf("%i", total);
}

int main() {
    solve02b();

    return 0;
}


