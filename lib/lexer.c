//
// Created by bestf on 1/1/2024.
//

#include <malloc.h>
#include <ctype.h>
#include <string.h>
#include "lexer.h"

typedef struct Lexer {
    const char* content;
    int position;
} Lexer;

typedef int (*CharCallback)(int);

Lexer* lexer_create(const char* content) {
    Lexer* lexer = malloc(sizeof(Lexer));
    lexer->content = content;
    lexer->position = 0;

    return lexer;
}

void seek(Lexer *lexer) {
    while (isblank(lexer->content[lexer->position])) {
        lexer->position++;
    }
}

Token* lex_callback(Lexer *lexer, CharCallback callback, TokenType type) {
    if (!callback(lexer->content[lexer->position])) {
        return NULL;
    }

    int start = lexer->position;
    int end = lexer->position;

    while (lexer->content[end] != '\0' && callback(lexer->content[end])) {
        end++;
    }

    Token *token = malloc(sizeof(Token));
    token->type = type;
    token->value = &lexer->content[start];
    token->value_len = end - start;
    lexer->position = end;

    return token;
}

Token* lex_string(Lexer *lexer) {
    return lex_callback(lexer, isalpha, T_STRING);
}

Token* lex_number(Lexer *lexer) {
    return lex_callback(lexer, isdigit, T_NUMBER);
}

Token* lex_punctuation(Lexer *lexer) {
    if (lexer->content[lexer->position] == ':') {
        Token *token = malloc(sizeof(Token));
        token->type = T_COLON;
        token->value = &lexer->content[lexer->position];
        token->value_len = 1;
        lexer->position++;

        return token;
    }
    if (lexer->content[lexer->position] == ';') {
        Token *token = malloc(sizeof(Token));
        token->type = T_SEMICOLON;
        token->value = &lexer->content[lexer->position];
        token->value_len = 1;
        lexer->position++;

        return token;
    }
    if (lexer->content[lexer->position] == ',') {
        Token *token = malloc(sizeof(Token));
        token->type = T_COMMA;
        token->value = &lexer->content[lexer->position];
        token->value_len = 1;
        lexer->position++;

        return token;
    }

    return NULL;
}

Token* lexer_next_token(Lexer* lexer) {
    seek(lexer);

    if (lexer->content[lexer->position] == '\0') {
        return NULL;
    }

    Token *token;
    token = lex_string(lexer);
    if (token != NULL) {
        return token;
    }
    token = lex_number(lexer);
    if (token != NULL) {
        return token;
    }
    token = lex_punctuation(lexer);
    if (token != NULL) {
        return token;
    }

    return NULL;
}

char* lexer_token_value(Token *token) {
    int len = token->value_len;
    char* dest = malloc(len + 1);

    strncpy(dest, token->value, len);
    dest[len] = '\0';

    return dest;
}

void lexer_free(Lexer* lexer) {
    free(lexer);
}




