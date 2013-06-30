#ifndef CRANBERRY_TOKEN_H
#define CRANBERRY_TOKEN_H

enum token {
    END_OF_FILE = 0,
    PERCENT,
    EQUAL,
    L_PAREN,
    R_PAREN,
    COMMA,
    SEMICOLON,
    PERIOD,
    INDEFINITE_ARTICLE,
    IS,
    HAS,
    CAN,
    WITH,
    THAT,
    AND,
    IDENTIFIER,
    PROPERTY
};

/*
#define PERCENT 1
#define EQUAL 2
#define L_PAREN 3
#define R_PAREN 4
#define COMMA 5
#define PERIOD 6
#define INDEFINITE_ARTICLE 7
#define IS 8
#define HAS 9
#define CAN 10
#define WITH 11
#define THAT 12
#define AND 13
#define IDENTIFIER 14
#define ERROR 15
#define END_OF_FILE 16
*/
#endif
