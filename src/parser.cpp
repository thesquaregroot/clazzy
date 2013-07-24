
// for parsing
#include "h/parser.h"
#include "h/class_def.h"
#include "h/function.h"
#include "h/member.h"
#include "h/token.h"
#include "h/language.h"
#include "h/language_factory.h"
#include "h/type_hint.h"
// system headers
#include <FlexLexer.h>
#include <vector>
#include <map>
#include <cstdlib>
#include <thread>
#include <mutex>
using namespace cranberry;
using namespace std;

// bool debug_enabled = false
// int lookahead
// FlexLexer *lex
// vector<class_def> classes
// vector<langauge*> langs
// map<string, string> properties
// mutex *io_mutex

parser::parser(FlexLexer *lexer)
{
        lex = lexer;
        io_mutex = new mutex();
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

        // debug data structures
        if (debug_enabled) {
                cout << "\nParsing complete:\n";
                // debug classes
                cout << "-Classes:\n";
                for (class_def c : classes) {
                        cout << "\t" << c.get_name() << "\n";
                        vector<member> members = c.get_members();
                        if (members.size() > 0) {
                                cout << "\t  ( ";
                                for (member m : members) {
                                        cout << m.get_type().to_string() << ":" << m.get_name() << " ";
                                }
                                cout << ")\n";
                        }
                        for (function f : c.get_functions()) {
                                cout << "\t\t" << f.get_name() << " ";
                                cout << "[ ";
                                for (auto &arg : f.get_parameters()) {
                                        cout << arg.second.to_string() << ":" << arg.first << " ";
                                }
                                cout << "]\n";
                        }
                }
                cout << "\n";
                // debug properties
                cout << "-Properties:\n";
                for (auto prop : properties) {
                        cout << "\t" << prop.first << " : " << prop.second + "\n";
                }
                // additional newline
                cout << "\n";
        }
}

// for threading langauge implementation of paser::write()
// not a member function
void write_langauge(
                        const language *lang,
                        const vector<class_def> &classes,
                        const map<string, string> &properties,
                        mutex *io_mutex
        )        
{
        io_mutex->lock();
        cout << "Writing " << lang->get_name() << " code..." << endl;
        io_mutex->unlock();

        lang->create(classes, properties);

        io_mutex->lock();
        cout << lang->get_name() << " complete." << endl;
        io_mutex->unlock();
}

void parser::write() const
{
        // write all language files
        vector<thread*> threads;
        for (unsigned int i=0; i<langs.size(); i++) {
                threads.push_back(new thread(
                                        write_langauge,
                                        langs.at(i),
                                        classes,
                                        properties,
                                        io_mutex
                                )
                        );
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
        if (exit_on_eof && lookahead == END_OF_FILE) {
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
        // save property
        properties[key] = value;
        // special propcessing
        if (key == "LANGUAGE") {
                // split on commas
                unsigned int start = 0;
                unsigned int length = 0;
                while ((start+length) < value.size()) {
                        while (value[start + length] != ',' && (start+length) < value.size())
                                length++;

                        string name = value.substr(start, length);
                        if (debug_enabled)
                                cout << "Found langauge: " + name;
                        // move start and length to after the comma
                        start = start + length + 1;
                        length = 0;
                        // get langauge with this name
                        language *l = language_factory::get_language(name, io_mutex, debug_enabled);
                        if (l == 0) {
                                error("Invalid language: " + name);
                        } else {
                                langs.push_back(l);
                        }
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
        string name;
        string parent;

        switch (lookahead) {
        case INDEFINITE_ARTICLE:
                // normal class definition
                next_token();
                if (lookahead != IDENTIFIER) {
                        // could not get class name
                        error("Invalid identifier: " + token_text() + ".");
                }
                name = token_text();
                types.add_type(name);
                c = class_def(name);
                next_token();
                parse_definition_list(c);
                break;
        case IDENTIFIER:
                // typedef or extension-type definition
                name = token_text();
                types.add_type(name);
                c = class_def(name);
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
        if (lookahead == PERIOD) {
                // done with this definition
                return;
        }
        if (lookahead != SEMICOLON) {
                // does not match a rule
                error("Invalid token '" + token_text() + "' following class definition.");
        }
        // SEMICOLON
        next_token();
        if (lookahead == AND) {
                next_token();
                parse_definition(c);
                // require period after "AND"
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
        if (lookahead == COMMA) {
                // continue with rest of list
                next_token();
                if (lookahead != IDENTIFIER) {
                        // must be done with action list
                        error("Invalid token '" + token_text() + "' following comma in action list.");
                }
                // IDENTIFIER -- more to list
                parse_action_list(c);
        }
        // no comma, must be done with list
}

void parser::parse_action(class_def& c)
{
        debug("Parsing action.");
        if (lookahead == STATIC) {
                // TODO: handle static modifier
                next_token();
                parse_action(c);
                return;
        }
        if (lookahead == READ_ONLY) {
                // TODO: handle read-only modifier
                next_token();
                parse_action(c);
                return;
        }
        
        type_hint r_type = parse_type_hint();
        if (lookahead != IDENTIFIER) {
                error("Invalid function definition.");
        }
        function f(r_type, token_text());

        next_token();
        if (lookahead == L_PAREN) {
                next_token();
                parse_parameter_list(f);
                if (lookahead != R_PAREN) {
                        error("Expected ')' after parameter list.");
                }
                // R_PAREN
                next_token();
        }
        c.add_function(f);
}

void parser::parse_parameter_list(function &f)
{
        debug("Parsing parameter list.");
        type_hint t = parse_type_hint();
        if (lookahead != IDENTIFIER) {
               error("Invalid parameter list, expected identifier at token '" + token_text() + "'."); 
        }
        f.add_parameter(t, token_text());
        next_token();
        if (lookahead != COMMA) {
                // must be done
                return;
        }
        next_token();
        // COMMA
        if (lookahead != IDENTIFIER) {
               error("Invalid parameter list, expected identifier at token '" + token_text() + "'."); 
        }
        parse_parameter_list(f);
}

void parser::parse_attribute_list(class_def& c)
{
        debug("Parsing attribute list.");
        
        type_hint t = parse_type_hint();
        if (lookahead != IDENTIFIER) {
                error("Invalid attribute list.");
        }

        member m(t, token_text());
        c.add_member(m);
        next_token();
        if (lookahead != COMMA) {
                // must be done
                return;
        }
        // COMMA
        next_token();
        parse_attribute_list(c);
}

type_hint parser::parse_type_hint()
{
        if (lookahead != IDENTIFIER) {
                error("Invalid type name: " + token_text() + ".");
        }
        string name = token_text();
        if (!types.is_defined(name)) {
                error("Invalid type: '" + name + "'.");
        }
        next_token();
        vector<type_hint> generics;
        if (lookahead == L_BRACKET) {
                if (!types.is_generic(name)) {
                        error("Type '" + name + "' is not generic.");
                }
                next_token();
                generics = parse_generic_type_list();
                if (lookahead != R_BRACKET) {
                        error("Expected '>' after generic list.");
                }
                next_token();
        }
        return type_hint(name, generics);
}

vector<type_hint> parser::parse_generic_type_list()
{
        vector<type_hint> generics;
        type_hint t = parse_type_hint();
        generics.push_back(t);
        if (lookahead != COMMA) {
                // must be done
                return generics;
        } else {
                next_token();
                for (type_hint future_hint : parse_generic_type_list()) {
                        generics.push_back(future_hint);
                }
        }
        return generics;
}
