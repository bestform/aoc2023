//
// Created by bestf on 1/1/2024.
//

#ifndef AOC2023_LEXER_H
#define AOC2023_LEXER_H

typedef enum {
    T_STRING,
    T_NUMBER,
    T_COMMA,
    T_SEMICOLON,
    T_COLON,
    T_STAR,
    T_SLASH,
    T_MINUS,
    T_PLUS,
    T_AND,
    T_EQUALS,
    T_PERCENT,
    T_DOLLAR,
    T_AT,
    T_PERIOD,
    T_HASH,
} TokenType;

typedef struct {
    TokenType type;
    const char* value;
    int value_len;
    int position;
} Token;

typedef struct Lexer Lexer;

Lexer* lexer_create(const char* content);
Token* lexer_next_token(Lexer* lexer);
char* lexer_token_value(Token *token);
void lexer_free(Lexer* lexer);

#endif //AOC2023_LEXER_H
