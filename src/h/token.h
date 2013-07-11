#ifndef CRANBERRY_TOKEN_H
#define CRANBERRY_TOKEN_H

namespace cranberry {
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
}

#endif
