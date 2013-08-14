%{
#include <iostream>
#include <fstream>
#include <cstdlib>
#include "h/token.h"
#include "h/parser.h"
using namespace clazzy;
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
    /* access modifiers */
(visible)|(VISIBLE)                     { return VISIBLE; }
(hidden)|(HIDDEN)                       { return HIDDEN; }
(child-visible)|(CHILD-VISIBLE)         { return CHILD_VISIBLE; }
(assembly-visible)|(assembly-visible)   { return ASSEMBLY_VISIBLE; }
    /* free-text */
[a-zA-Z_\-]+                { return IDENTIFIER; }
[a-zA-Z_]+=[^\n;]*          { return PROPERTY; }
#[^\n]*                     /* skip # comments */
[ \t\n]+                    /* skip whitespace */
.                           {
                                //handle token errors
                                cout << "ERROR [Line " << yylineno << "]: illegal token \"" << yytext << "\"." << endl;
                                exit(1);
                            }

%%

void print_usage_error(char *arg0)
{
    cout << "Usage: " << arg0 << " [--debug] [input-file]" << endl;
    exit(1);
}

int main(int argc, char** argv)
{
    char *input = 0;
    bool debug = false;

    for (int i=1; i<argc; i++) {
        // get argument
        char *arg = argv[i];
        if (arg[0] == '-') {
            // some sort of option
            if (strcmp(arg, "--debug") == 0) {
                debug = true;
            } else {
                cerr << "Unrecognized argument: " << arg << "." << endl;
                print_usage_error(argv[0]);
            }
        } else {
            // no '-', must be file name
            input = arg;
        }
    }

    
    parser *p;
    if (input == 0) {
        p = new parser(new yyFlexLexer());
    } else {
        ifstream *in = new ifstream(input);
        if (in->is_open()) {
            p = new parser(new yyFlexLexer(in));
        } else {
            cerr << "Could not open file: " << input << "." << endl;
            print_usage_error(argv[0]);
        }
    }
    p->set_debug(debug);
    p->parse();
    p->write();
}

