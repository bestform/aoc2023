//
// Created by bestf on 1/3/2024.
//

#include <malloc.h>
#include <stdio.h>
#include <string.h>
#include "03.h"
#include "lexer.h"

#define INITIAL_CAPACITY 5
#define CAPACITY_JUMP 2

typedef struct Schematic {
    const char** lines;
    int line_count;
    int line_length;
    int capacity;
} Schematic;


Schematic *schematic_create() {
    Schematic *s = malloc(sizeof(Schematic));
    s->line_count = 0;
    s->line_length = 0;
    s->capacity = INITIAL_CAPACITY;
    s->lines = malloc(sizeof(char*) * INITIAL_CAPACITY);

    return s;
}

void schematic_free(Schematic *s) {
    free(s->lines);
    free(s);
}

void schematic_add_line(Schematic *s, const char *line) {
    if (strcmp(line, "") == 0) return;
    if (s->line_length == 0) {
        s->line_length = (int) strlen(line);
    } else {
        if (s->line_length != strlen(line)) {
            printf("all lines added must be of same length");
            exit(1);
        }
    }

    if (s->line_count == s->capacity) {
        s->lines = realloc(s->lines, sizeof(char*) * (s->capacity + CAPACITY_JUMP));
        s->capacity += CAPACITY_JUMP;
        if (s->lines == NULL) {
            printf("Failed to allocate more memory for lines");
            exit(1);
        }
    }

    s->lines[s->line_count] = line;
    s->line_count++;
}

int token_is_symbol(const Token *token) {
    return
            (
                    token->type == T_AT ||
                    token->type == T_DOLLAR ||
                    token->type == T_PERCENT ||
                    token->type == T_EQUALS ||
                    token->type == T_AND ||
                    token->type == T_PLUS ||
                    token->type == T_SLASH ||
                    token->type == T_STAR ||
                    token->type == T_MINUS ||
                    token->type == T_HASH
            );
}

int token_is_star(const Token *token) {
    return token->type == T_STAR;
}

typedef struct {
    int x;
    int y;
    int* numbers;
    size_t numbers_count;
} Star;

typedef struct {
    Star* stars;
    size_t stars_count;
} Stars;

bool is_next_to_symbol(int position, int len, int row, char *symbols[], int line_length, int line_count) {
    int start_pos = position - 1;
    if (start_pos == -1) start_pos = 0;
    int end_pos = position + len;
    if (end_pos > line_length - 1) {
        end_pos = line_length - 1;
    }

    int start_row = row - 1;
    if (start_row < 0) start_row = 0;
    int end_row = row + 1;
    if (end_row >= line_count) {
        end_row = line_count - 1;
    }

    for (int i = start_pos; i <= end_pos; i++) {
        for (int j = start_row; j <= end_row; j++) {
            if (symbols[j][i] == 1 ) return 1;
        }
    }

    return 0;
}

void stars_add_or_create(Stars* stars, int x, int y, int number) {

    if (stars->stars_count == 0) {
        stars->stars = malloc(sizeof(Star));
    }
    bool is_new = true;
    size_t index = -1;
    for (int i = 0; i < stars->stars_count; i++) {
        if (stars->stars[i].x == x && stars->stars[i].y == y) {
            index = i;
            is_new = false;
            break;
        }
    }
    if (index == -1) {
        index = stars->stars_count;
        stars->stars_count++;
        stars->stars = realloc(stars->stars, sizeof(Star) * stars->stars_count);
        index = stars->stars_count - 1;
    }

    stars->stars[index].x = x;
    stars->stars[index].y = y;
    if (is_new) {
        stars->stars[index].numbers_count = 1;
    } else {
        stars->stars[index].numbers_count++;
    }

    if (is_new) {
        stars->stars[index].numbers = malloc(sizeof(int));
    } else {
        stars->stars[index].numbers = realloc(stars->stars[index].numbers, sizeof(int) * stars->stars[index].numbers_count);
    }
    stars->stars[index].numbers[stars->stars[index].numbers_count - 1] = number;

}

void check_stars(Stars* stars, int number, int position, int len, int row, char *symbols[], int line_length, int line_count) {
    int start_pos = position - 1;
    if (start_pos == -1) start_pos = 0;
    int end_pos = position + len;
    if (end_pos > line_length - 1) {
        end_pos = line_length - 1;
    }

    int start_row = row - 1;
    if (start_row < 0) start_row = 0;
    int end_row = row + 1;
    if (end_row >= line_count) {
        end_row = line_count - 1;
    }

    for (int i = start_pos; i <= end_pos; i++) {
        for (int j = start_row; j <= end_row; j++) {
            if (symbols[j][i] == 1 ) {
                stars_add_or_create(stars, i, j, number);
            }
        }
    }

}

int schematic_gear_ratio_sum(Schematic *s) {
    char *star_symbols[s->line_count];

    for (int i = 0; i < s->line_count; i++) {
        star_symbols[i] = (char *) malloc(sizeof(char) * s->line_length);
    }

    for (int i = 0; i < s->line_count; i++) {
        for (int j = 0; j < s->line_length; j++) {
            star_symbols[i][j] = 0;
        }
    }

    size_t stars_count = 0;

    for (int i = 0; i < s->line_count; i++) {
        Lexer *lexer = lexer_create(s->lines[i]);
        Token *token;
        while ((token = lexer_next_token(lexer)) != NULL) {
            if (token_is_star(token)) {
                star_symbols[i][token->position] = 1;
                stars_count++;
            }
            lexer_token_free(token);
        }
        lexer_free(lexer);
    }

    Stars *stars = malloc(sizeof(Stars));
    stars->stars_count = 0;
    stars->stars = malloc(sizeof(Star) * stars_count);

    int total = 0;
    for (int i = 0; i < s->line_count; i++) {
        Lexer *lexer = lexer_create(s->lines[i]);
        Token *token;
        while ((token = lexer_next_token(lexer)) != NULL) {
            if (token->type == T_NUMBER) {
                int number = atoi(lexer_token_value(token));
                check_stars(stars, number, token->position, token->value_len, i, star_symbols, s->line_length, s->line_count);
            }
            free(token);
        }
        lexer_free(lexer);
    }

    for (int i = 0; i < s->line_count; i++) {
        free(star_symbols[i]);
    }

    for (int i = 0; i < stars->stars_count; i++) {
        if (stars->stars[i].numbers_count == 2) {
            total += stars->stars[i].numbers[0] * stars->stars[i].numbers[1];
        }
        free(stars->stars[i].numbers);
    }

    free(stars->stars);

    return total;
}

int schematic_sum(Schematic *s) {
    char *symbols[s->line_count];

    for (int i = 0; i < s->line_count; i++) {
        symbols[i] = (char *) malloc(sizeof(char) * s->line_length);
    }

    for (int i = 0; i < s->line_count; i++) {
        for (int j = 0; j < s->line_length; j++) {
            symbols[i][j] = 0;
        }
    }

    for (int i = 0; i < s->line_count; i++) {
        Lexer *lexer = lexer_create(s->lines[i]);
        Token *token;
        while ((token = lexer_next_token(lexer)) != NULL) {
            if (token_is_symbol(token)) {
                symbols[i][token->position] = 1;
            }
            lexer_token_free(token);
        }
        lexer_free(lexer);
    }

    int total = 0;
    for (int i = 0; i < s->line_count; i++) {
        Lexer *lexer = lexer_create(s->lines[i]);
        Token *token;
        while ((token = lexer_next_token(lexer)) != NULL) {
            if (token->type == T_NUMBER) {
                if (is_next_to_symbol(token->position, token->value_len, i, symbols, s->line_length, s->line_count)) {
                    char* value = lexer_token_value(token);
                    int num = atoi(value);
                    total += num;
                    free(value);
                }
            }
            free(token);
        }
        lexer_free(lexer);
    }

    for (int i = 0; i < s->line_count; i++) {
        free(symbols[i]);
    }

    return total;
}







