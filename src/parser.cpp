
// for parsing
#include "h/parser.h"
#include "h/class_def.h"
#include "h/function.h"
#include "h/member.h"
#include "h/token.h"
// language implementations
#include "h/lang_cpp.h"
// system headers
#include <FlexLexer.h>
#include <vector>
#include <map>
#include <cstdlib>
#include <thread>
using namespace cranberry;
using namespace std;

// bool debug_enabled = false
// int lookahead
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
        next_token();
        while (lookahead != END_OF_FILE) {
                parse_statement();
                next_token(false); // EOFs are okay here (and only here)
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
                cout << "DEBUG [Line " << lex->lineno() << "]: " << str << " [token=" << token_text() << "]" << endl;
}

void parser::error(string err) const
{
        cerr << "ERROR [Line " << lex->lineno() << "]: " << err << endl;
        exit(1);
}

void parser::next_token(bool exit_on_eof /* = true */) {
        lookahead = lex->yylex();
        if (lookahead == END_OF_FILE) {
                error("Unexpected end of file.");
        }
}

string parser::token_text() const {
        return lex->YYText();
}

//
// This is where the magic happens
//
void parser::parse_statement()
{
        
        switch (lookahead) {
        case PERCENT:
                next_token();
                parse_property();
                break;
        case INDEFINITE_ARTICLE:
        case IDENTIFIER:
                next_token();
                classes.push_back(parse_type_definition());
                break;
        default:
                // not a valid statement
                error("Unexpected token: " + token_text());
        } 
}

void parser::parse_property()
{
        debug("Parsing property.");

        if (lookahead != PROPERTY) {
                error("Key-value pair expected after \"%\" token.");
        }
        string property = token_text();
        string key = property.substr(0, property.find('='));
        string value = property.substr(property.find('=')+1);
        if (key == "LANGUAGE") {
                // add new languages here
                if (value == "C++") {
                        langs.push_back(new lang_cpp());
                } else {
                        error("Invalid langauge.");
                }
        }
        next_token();
        if (lookahead != SEMICOLON) {
                // not sure if this is possible
                error("Invalid delimiter for property.");
        }
}

class_def parser::parse_type_definition()
{
        debug("Parsing type definition.");

        class_def c;
        string parent;

        switch (lookahead) {
        case INDEFINITE_ARTICLE:
                // normal class definition
                next_token();
                if (lookahead != IDENTIFIER) {
                        // could not get class name
                        error("Invalid identifier: " + token_text() + ".");
                }
                c = class_def(token_text());
                next_token();
                parse_definition_list(c);
                break;
        case IDENTIFIER:
                // typedef or extension-type definition
                c = class_def(token_text());
                next_token();
                if (lookahead != IS) {
                        // straight definition, get it and go
                        parse_definition_list(c);
                        return c;
                }
                next_token();
                if (lookahead != INDEFINITE_ARTICLE) {
                        error("Expected token 'a/an' following 'is', instead found '" + token_text() + "'.");
                }
                next_token();
                if (lookahead != IDENTIFIER) {
                        error("Invalid identifier after 'is a' construct.");
                }
                c.add_parent(token_text());
                // got parent, check for additional definition
                next_token();
                if (lookahead == PERIOD) {
                        return c;
                } else if (lookahead == THAT) {
                        next_token();
                        parse_definition_list(c);
                        return c;
                } else {
                        error("Unexpected token '" + token_text() + "'.");
                }
                break;
        default:
                error("Invalid type definition.");
        }

        return c;
}

void parser::parse_definition_list(class_def& c)
{
        debug("Parsing definition list.");

        parse_definition(c);
        next_token();
        if (lookahead == PERIOD) {
                // done with this definition
                return;
        }
        if (lookahead != COMMA) {
                // does not match a rule
                error("Invalid token '" + token_text() + "' following class definition.");
        }
        // COMMA
        next_token();
        if (lookahead == AND) {
                next_token();
                parse_definition(c);
                // require period after "AND"
                next_token();
                if (lookahead != PERIOD) {
                        error("Class definition not ended with a period.");
                }
        } else {
                parse_definition_list(c);
        }
}

void parser::parse_definition(class_def& c)
{
        debug("Parsing definition.");

        if (lookahead == CAN) {
                next_token();
                parse_action_list(c);
        } else if (lookahead == HAS) {
                next_token();
                parse_attribute_list(c);
        } else {
                error("Invalid type definition.");
        }
}

void parser::parse_action_list(class_def& c)
{
        debug("Parsing action list.");

        parse_action(c);
        next_token();
        if (lookahead != COMMA) {
                // must be done with action list
                return;
        }
        // more to list
        next_token();
        parse_action_list(c);
}

void parser::parse_action(class_def& c)
{
        debug("Parsing action.");

        if (lookahead != IDENTIFIER) {
                error("Invalid function definition.");
        }
        function f(token_text());
        next_token();
        if (lookahead == L_PAREN) {
                parse_parameter_list(f);
                if (lookahead != R_PAREN) {
                        error("Expected ')' after parameter list.");
                }
        }
        c.add_function(f);
}

void parser::parse_parameter_list(function &f)
{
        debug("Parsing parameter list.");

        if (lookahead != IDENTIFIER) {
               error("Invalid parameter list."); 
        }
        f.add_parameter(token_text());
        next_token();
        if (lookahead != COMMA) {
                // must be done
                return;
        }
        // COMMA
        if (lookahead != IDENTIFIER) {
                error("Invalid parameter list.");
        }
        parse_parameter_list(f);
}

void parser::parse_attribute_list(class_def& c)
{
        debug("Parsing attribute list.");

        if (lookahead != IDENTIFIER) {
                error("Invalid attribute list.");
        }

        do {
                member m(token_text());
                c.add_member(m);
                next_token();
        } while (lookahead == IDENTIFIER);
}

