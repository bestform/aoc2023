//
// Created by bestf on 12/30/2023.
//

#ifndef AOC2023_02_H

typedef struct {
    int blues;
    int greens;
    int reds;
} Round;

typedef struct {
    char* id;
    Round** rounds;
    int num_rounds;
} Game;

Game *game_for_line(char* line);

Round max_throws_for_game(Game *game);

#define AOC2023_02_H

#endif //AOC2023_02_H
