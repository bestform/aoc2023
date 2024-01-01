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
} TokenType;

typedef struct {
    TokenType type;
    const char* value;
    int value_len;
} Token;

typedef struct Lexer Lexer;

Lexer* lexer_create(const char* content);
Token* lexer_next_token(Lexer* lexer);
char* lexer_token_value(Token *token);
void lexer_free(Lexer* lexer);

#endif //AOC2023_LEXER_H
