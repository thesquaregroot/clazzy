%{
#include <iostream>
#include <cstdlib>
#include "h/token.h"
#include "h/parser.h"
using namespace cranberry;
using namespace std;
%}

%option noyywrap
%option yylineno

%%

"%"                         { return PERCENT; }
"="                         { return EQUAL; }
"("                         { return L_PAREN; }
")"                         { return R_PAREN; }
"<"                         { return L_BRACKET; }
">"                         { return R_BRACKET; }
","                         { return COMMA; }
";"                         { return SEMICOLON; }
"."                         { return PERIOD; }
(a(n)?)|(A(N)?)             { return INDEFINITE_ARTICLE; }
(is)|(IS)                   { return IS; }
(has)|(HAS)                 { return HAS; }
(can)|(CAN)                 { return CAN; }
(with)|(WITH)               { return WITH; }
(and)|(AND)                 { return AND; }
(constant)|(CONSTANT)       { return CONSTANT; }
(static)|(STATIC)           { return STATIC; }
(reference)|(REFERENCE)     { return REFERENCE; }
(read\ only)|(READ\ ONLY)   { return READ_ONLY; }
[a-zA-Z_\-]+                { return IDENTIFIER; }
[a-zA-Z_]+=[^;]*            { return PROPERTY; }
#[^\n]*                     /* skip # comments */
[ \t\n]+                    /* skip whitespace */
.                           {
                                //handle token errors
                                cout << "ERROR [Line " << yylineno << "]: illegal token \"" << yytext << "\"." << endl;
                                exit(1);
                            }

%%

int main(int argc, char** argv)
{
    parser p(new yyFlexLexer());
    p.set_debug(true);
    p.parse();
    p.write();
}

