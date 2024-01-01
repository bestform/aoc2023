//
// Created by bestf on 12/30/2023.
//

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include "02.h"
#include "lexer.h"

typedef enum {
    P_START,
    P_LOOKING_FOR_NUMBER,
    P_LOOKING_FOR_COLOR,
    P_DONE,
} ParseState;

Game *game_for_line(char* line) {
    Game *game = malloc(sizeof(Game));

    int allocated_rounds = 1;
    game->rounds = malloc(sizeof(Round) * allocated_rounds);
    game->rounds[0] = malloc(sizeof(Round));
    game->rounds[0]->reds = 0;
    game->rounds[0]->greens = 0;
    game->rounds[0]->blues = 0;

    Lexer *lexer = lexer_create(line);
    Token *token;

    token = lexer_next_token(lexer); // Game
    free(token);

    // get game id
    token = lexer_next_token(lexer); // game number
    char* game_number = lexer_token_value(token);
    game->id = game_number;
    free(token);

    int number;
    int round_num = 1;

    ParseState state = P_START;
    token = lexer_next_token(lexer);
    while (token != NULL) {
        char *str_value = lexer_token_value(token);
        switch (state) {
            case P_START:
                if (round_num > allocated_rounds) {
                    allocated_rounds += 1;
                    game->rounds = realloc(game->rounds, sizeof(Round)*allocated_rounds);
                    game->rounds[round_num - 1] = malloc(sizeof(Round));
                    game->rounds[round_num - 1]->reds = 0;
                    game->rounds[round_num - 1]->greens = 0;
                    game->rounds[round_num - 1]->blues = 0;
                }
                state = P_LOOKING_FOR_NUMBER;
                break;
            case P_LOOKING_FOR_NUMBER:
                number = atoi(str_value);
                state = P_LOOKING_FOR_COLOR;
                break;
            case P_LOOKING_FOR_COLOR:
                if (strcmp(str_value, "red") == 0) {
                    game->rounds[round_num - 1]->reds = number;
                }
                if (strcmp(str_value, "green") == 0) {
                    game->rounds[round_num - 1]->greens = number;
                }
                if (strcmp(str_value, "blue") == 0) {
                    game->rounds[round_num - 1]->blues = number;
                }
                // check next token
                free(token);
                token = lexer_next_token(lexer);
                if (token == NULL) {
                    state = P_DONE;
                    break;
                }
                if (token->type == T_SEMICOLON) {
                    state = P_START;
                    round_num++;
                } else {
                    state = P_LOOKING_FOR_NUMBER;
                }

                break;
            case P_DONE:
                break;
        }
        free(str_value);
        if (state != P_START) {
            token = lexer_next_token(lexer);
        }

    }

    game->num_rounds = round_num;

    return game;
}

Round max_throws_for_game(Game *game) {
    Round round = {0};

    int max_red = 0;
    int max_green = 0;
    int max_blue = 0;


    for (int i = 0; i < game->num_rounds; i++) {
        Round *inspected_round = game->rounds[i];

        if (max_red < inspected_round->reds) {
            max_red = inspected_round->reds;
        }
        if (max_blue < inspected_round->blues) {
            max_blue = inspected_round->blues;
        }
        if (max_green < inspected_round->greens) {
            max_green = inspected_round->greens;
        }

    }

    round.blues = max_blue;
    round.greens = max_green;
    round.reds = max_red;

    return round;
}
