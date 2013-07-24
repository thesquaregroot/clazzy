#ifndef CRANBERRY_TOKEN_H
#define CRANBERRY_TOKEN_H

namespace cranberry {
    enum token {
        END_OF_FILE = 0,
        // special characters (incl. punctuation)
        PERCENT,
        EQUAL,
        L_PAREN,
        R_PAREN,
        L_BRACKET,
        R_BRACKET,
        COMMA,
        SEMICOLON,
        PERIOD,
        // normal keywords
        INDEFINITE_ARTICLE,
        IS,
        HAS,
        CAN,
        WITH,
        THAT,
        AND,
        // modifiers
        CONSTANT,
        STATIC,
        REFERENCE,
        READ_ONLY,
        // other
        IDENTIFIER,
        PROPERTY
    };
}

#endif
