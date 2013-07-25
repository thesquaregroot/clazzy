#ifndef __CRANBERRY_TOKEN_H__
#define __CRANBERRY_TOKEN_H__

namespace cranberry {
    enum token {
        END_OF_FILE,
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
