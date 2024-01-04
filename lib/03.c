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

bool is_next_to_symbol(int position, int len, int row, const long long int symbols[], int line_length, int line_count) {
    int start_pos = position - 1;
    if (start_pos == -1) start_pos = 0;
    int end_pos = position + len;
    if (end_pos > line_length - 1) {
        end_pos = line_length - 1;
    }

    int mask = 0;
    for (int i = start_pos; i <= end_pos; i++) {
        mask |= 1<<i;
    }

    int start_row = row - 1;
    if (start_row < 0) start_row = 0;
    int end_row = row + 1;
    if (end_row >= line_count) {
        end_row = line_count - 1;
    }

    for (int i = start_row; i <= end_row; i++) {
        if ((mask & symbols[i]) >= 1 ) return 1;
    }

    return 0;
}

int schematic_sum(Schematic *s) {

    long long int symbols[s->line_count - 1];
    for (int i = 0; i < s->line_count; i++) {
        symbols[i] = 0;
    }

    for (int i = 0; i < s->line_count; i++) {
        Lexer *lexer = lexer_create(s->lines[i]);
        Token *token;
        while ((token = lexer_next_token(lexer)) != NULL) {
            if (token_is_symbol(token)) {
                symbols[i] |= 1<<token->position;
            }
            free(token);
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
                    printf("%i\n", num);
                    total += num;
                    free(value);
                }
                symbols[i] |= 1<<token->position;
            }
            free(token);
        }
        lexer_free(lexer);
    }

    return total;
}







