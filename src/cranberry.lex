%{
#include <iostream>
#include <cstdlib>
#include "h/token.h"
#include "h/parser.h"
using namespace std;
%}

%option noyywrap
%option yylineno

%%

"%"                 { return PERCENT; }
"="                 { return EQUAL; }
"("                 { return L_PAREN; }
")"                 { return R_PAREN; }
","                 { return COMMA; }
";"                 { return SEMICOLON; }
"."                 { return PERIOD; }
(a(n)?)|(A(N)?)     { return INDEFINITE_ARTICLE; }
(is)|(IS)           { return IS; }
(has)|(HAS)         { return HAS; }
(can)|(CAN)         { return CAN; }
(with)|(WITH)       { return WITH; }
(that)|(THAT)       { return THAT; }
(and)|(AND)         { return AND; }
[a-zA-Z_\-]+        { return IDENTIFIER; }
[a-zA-Z_]+=[^;]*    { return PROPERTY; }
[ \t\n]+            /* skip whitespace */
.                   {
                        //handle errors
                        cout << "ERROR at line " << yylineno << ": illegal token \"" << yytext << "\"." << endl;
                        exit(1);
                    }

%%

int main(int argc, char** argv)
{
    parser p(new yyFlexLexer());
    p.parse();
    p.write();
}
