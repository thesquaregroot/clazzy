
#include "h/token.h"
#include "h/parser.h"
#include "h/language.h"
#include "h/class_def.h"
#include <FlexLexer.h>
#include <vector>
#include <map>
#include <cstdlib>
#include <thread>
using namespace std;

// bool debug_enabled = false
// FlexLexer *lex
// vector<class_def> classes
// vector<langauge*> langs
// map<string, string> properties

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

// for threading langauge implementation
// not a member function
void write_langauge(const language *lang, const vector<class_def>& classes)
{
        cout << "Writing " << lang->get_name() << " code..." << endl;
        lang->create(classes);
        cout << lang->get_name() << " complete." << endl;
}


void parser::write() const
{
        // write all language files
        vector<thread*> threads;
        for (unsigned int i=0; i<langs.size(); i++) {
                threads.push_back(new thread(write_langauge, langs.at(i), classes));
        }
        for (thread *t : threads) {
                t->join();
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
        string parent;

        switch (lookahead) {
        case INDEFINITE_ARTICLE:
                // normal class definition
                lookahead = lex->yylex();
                if (lookahead == IDENTIFIER) {
                        name = lex->YYText();
                } else {
                        // could not get class name
                        error("Invalid identifier: " + string(lex->YYText()) + ".");
                }
                c = class_def(name);
                parse_definition_section(lex->yylex(), c);
                break;
        case IDENTIFIER:
                // typedef or extension-type definition
                c = class_def(lex->YYText());
                lookahead = lex->yylex();
                if (lookahead != IS) {
                        error("Expected token 'is' following identifier '" + name + "'.");
                }
                lookahead = lex->yylex();
                if (lookahead != INDEFINITE_ARTICLE) {
                        error("Expected token 'a/an' following 'is', instead found '" + string(lex->YYText()) + "'.");
                }
                // TODO (finish two types)
                break;
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

