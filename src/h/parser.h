#ifndef PARSER_H
#define PARSER_H

#include <vector>
#include "class_def.h"
#include "language.h"

class FlexLexer;

class parser {
    private:
        FlexLexer               *lex;
        std::vector<class_def>  classes;
        std::vector<language>   langs;

    public:
        parser(FlexLexer *lexer);
        ~parser();
        
        void parse();
        void write() const;
};

#endif
