
#include "h/token.h"
#include "h/parser.h"
#include "h/language.h"
#include "h/class_def.h"
#include <FlexLexer.h>
#include <vector>
#include <cstdlib>
using namespace std;

// bool debug_enabled = false
// FlexLexer *lex
// vector<class_def> classes
// vector<langauge*> langs

parser::parser(FlexLexer *lexer)
{
        lex = lexer;
}

parser::~parser()
{
        delete lex;

        while (langs.size() > 0) {
                delete langs.front();
                langs.erase(langs.begin());
        }
}

void parser::set_debug(bool debug)
{
        debug_enabled = debug;
}

void parser::parse()
{
        for (int token = lex->yylex(); token != END_OF_FILE; token = lex->yylex()) {
                parse_statement(token);
        }
}

void parser::write() const
{
        // write all language files
        for (unsigned int i=0; i<langs.size(); i++) {
                const language *lang = langs.at(i);
                cout << "Writing " << lang->get_name() << " code..." << endl;
                lang->create(classes);
        }
}



// private functions
void parser::debug(string str) const
{
        if (debug_enabled)
                cout << "DEBUG [Line " << lex->lineno() << "]: " << str << endl;
}

void parser::error(string err) const
{
        cerr << "ERROR [Line " << lex->lineno() << "]: " << err << endl;
        exit(1);
}


//
// This is where the magic happens
//
void parser::parse_statement(int lookahead)
{
        switch (lookahead) {
        case PERCENT:
                debug("Parsing property.");

                parse_property(lookahead);
                break;
        case INDEFINITE_ARTICLE:
        case IDENTIFIER:
                debug("Parsing type definition.");

                classes.push_back(parse_type_definition(lookahead));
                break;
        default:
                // not a valid statement
                error("Unexpected token: " + string(lex->YYText()));
        } 
}

void parser::parse_property(int lookahead)
{
        
}

class_def parser::parse_type_definition(int lookahead) const
{
        class_def c;
        string name;

        switch (lookahead) {
        case INDEFINITE_ARTICLE:
                // normal class definition
                lookahead = lex->yylex();
                if (lookahead == IDENTIFIER) {
                        name = lex->YYText();
                } else {
                        // could not get class name
                        error("Invalid identifier: " + string(lex->YYText()));
                }
                c = class_def(name);
                parse_definition_section(lex->yylex(), c);
                break;
        case IDENTIFIER:
                // typedef or extension-type definition
                // TODO
        default:
                error("Invalid type definition.");
        }

        return c;
}

void parser::parse_definition_section(int lookahead, class_def& c) const
{
        
}

void parser::parse_definition_list(int lookahead, class_def& c) const
{
        
}

void parser::parse_definition(int lookahead, class_def& c) const
{
        
}

void parser::parse_action_list(int lookahead, class_def& c) const
{

}

void parser::parse_action(int lookahead, class_def& c) const
{

}

void parser::parse_attribute_list(int lookahead, class_def& c) const
{

}

void parser::parse_parameters(int lookahead, class_def& c) const
{

}

void parser::parse_parameter_list(int lookahead, class_def& c) const
{

}

