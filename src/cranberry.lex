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
(that)|(THAT)               { return THAT; }
(and)|(AND)                 { return AND; }
(constant)|(CONSTANT)       { return CONSTANT; }
(static)|(STATIC)           { return STATIC; }
(reference)|(REFERENCE)     { return REFERENCE; }
(read\ only)|(READ\ ONLY)   { return READ_ONLY; }
    /*
(array)|(ARRAY)             { return GENERIC_TYPE; }
(deque)|(DEQUE)             { return GENERIC_TYPE; }
(list)|(LIST)               { return GENERIC_TYPE; }
(set)|(SET)                 { return GENERIC_TYPE; }
(stack)|(STACK)             { return GENERIC_TYPE; }
(queue)|(QUEUE)             { return GENERIC_TYPE; }
(map)|(MAP)                 { return GENERIC_TYPE; }
(pointer)|(POINTER)         { return GENERIC_TYPE; }
(byte)|(BYTE)               { return PRIMITIVE_TYPE; }
(short)|(SHORT)             { return PRIMITIVE_TYPE; }
(integer)|(INTEGER)         { return PRIMITIVE_TYPE; }
(long)|(LONG)               { return PRIMITIVE_TYPE; }
(character)|(CHARACTER)     { return PRIMITIVE_TYPE; }
(string)|(STRING)           { return PRIMITIVE_TYPE; }
(float)|(FLOAT)             { return PRIMITIVE_TYPE; }
(double)|(DOUBLE)           { return PRIMITIVE_TYPE; }
(boolean)|(BOOLEAN)         { return PRIMITIVE_TYPE; }
(void)|(VOID)               { return PRIMITIVE_TYPE; }
    */
[a-zA-Z_\-]+                { return IDENTIFIER; }
[a-zA-Z_]+=[^;]*            { return PROPERTY; }
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

