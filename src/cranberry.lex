%{
#include <iostream>
#include "h/token.h"
using namespace std;
%}

%option noyywrap
%option yylineno

%%

[ \t\n]+          /* skip whitespace */
%               { return PERCENT; }
(a(n)?)|(A(N)?) { return INDEFINITE_ARTICLE; }
(is)|(IS)       { return IS; }
(has)|(HAS)     { return HAS; }
(can)|(CAN)     { return CAN; }
(with)|(WITH)   { return WITH; }
(that)|(THAT)   { return THAT; }
(and)|(AND)     { return AND; }
[a-zA-Z_-]+     { return IDENTIFIER; }
[^\n\t ]+       { return VALUE; }

%%

int main(int argc, char** argv)
{
    FlexLexer* lexer = new yyFlexLexer;
    while (lexer->yylex() != 0) {
        cout << "[" << lexer->lineno() << "] Token: " << lexer->YYText() << "\n";
    }
}
