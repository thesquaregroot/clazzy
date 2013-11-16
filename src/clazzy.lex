%{
#include <iostream>
#include <fstream>
#include <cstdlib>
#include "h/token.h"
#include "h/parser.h"
#include "h/version.h"
using namespace clazzy;
using namespace std;
%}

%option noyywrap
%option yylineno

%%

"@"                         { return AT_SYMBOL; }
"%"                         { return PERCENT; }
"="                         { return EQUAL; }
"("                         { return L_PAREN; }
")"                         { return R_PAREN; }
"<"                         { return L_BRACKET; }
">"                         { return R_BRACKET; }
","                         { return COMMA; }
";"                         { return SEMICOLON; }
"."                         { return PERIOD; }
"@construct"                { return CONSTRUCTOR; }
"@CONSTRUCT"                { return CONSTRUCTOR; }
"@destruct"                 { return DESTRUCTOR; }
"@DESTRUCT"                 { return DESTRUCTOR; }
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
(get)|(GETS)                { return GETTER; }
(set)|(SETS)                { return SETTER; }
(getset)|(GET_SET)          { return GET_SET; }
    /* access modifiers */
(visible)|(VISIBLE)                     { return VISIBLE; }
(hidden)|(HIDDEN)                       { return HIDDEN; }
(child-visible)|(CHILD-VISIBLE)         { return CHILD_VISIBLE; }
(assembly-visible)|(assembly-visible)   { return ASSEMBLY_VISIBLE; }
    /* Describers */
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

void print_version()
{
    cout << "Clazzy, version " << CLAZZY_VERSION << endl;
    cout << endl;
    cout << "Copyright (C) 2013, Andrew Groot" << endl;
    cout << "Licensed under the GNU GPL version 3" << endl;
    cout << endl;
    cout << "This is free software; you are free to change and redistribute it." << endl;
    cout << "There is NO WARRANTY, to the extent permitted by law." << endl;
}

void print_usage(char *arg0)
{
    cout << "Usage: " << arg0 << " --version" << endl;
    cout << "       " << arg0 << " --help" << endl;
    cout << "       " << arg0 << " [--debug] [input-file]" << endl;
    cout << endl;
    cout << "  --version    Display the version of clazzy" << endl;
    cout << "  --help       Display this help text" << endl;
    cout << "  --debug      Enables verbose output" << endl;
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
            } else if (strcmp(arg, "--version") == 0) {
                print_version();
                exit(0);
            } else if (strcmp(arg, "--help") == 0) {
                print_usage(argv[0]);
                exit(1);
            } else {
                cerr << "Unrecognized argument: " << arg << "." << endl;
                print_usage(argv[0]);
                exit(1);
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
            print_usage(argv[0]);
            exit(1);
        }
    }

    p->set_debug(debug);
    p->parse();
    p->write();
}

