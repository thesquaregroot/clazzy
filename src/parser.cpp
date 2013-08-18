
// for parsing
#include "h/parser.h"
#include "h/class_def.h"
#include "h/method.h"
#include "h/member.h"
#include "h/token.h"
#include "h/language.h"
#include "h/language_factory.h"
#include "h/type_hint.h"
#include "h/access_type.h"
#include "h/validator.h"
// system headers
#include <FlexLexer.h>
#include <vector>
#include <map>
#include <cstdlib>
#include <thread>
#include <mutex>
using namespace clazzy;
using namespace std;

// bool _debug_enabled = false
// int _lookahead
// FlexLexer *_lex
// vector<class_def> _classes
// vector<langauge*> _langs
// map<string, string> _properties
// mutex *_io_mutex

parser::parser(FlexLexer *lexer)
{
        _lex = lexer;
        _io_mutex = new mutex();
}

parser::~parser()
{
        while (_langs.size() > 0) {
                delete _langs.front();
                _langs.erase(_langs.begin());
        }
}

void parser::set_debug(bool debug)
{
        _debug_enabled = debug;
}

void parser::parse()
{
        next_token();
        while (_lookahead != END_OF_FILE) {
                parse_statement();
                next_token(false); // EOFs are okay here (and only here)
        }

        // debug data structures
        if (_debug_enabled) {
                cout << "\nParsing complete:\n";
                // debug classes
                cout << "-Classes:\n";
                for (class_def c : _classes) {
                        cout << "\t" << c.get_name() << "\n";
                        for (type_hint p : c.get_parents()) {
                                cout << "\t\t-- " << p.to_string() << "\n";
                        }
                        cout << "\t\t(\n";
                        for (member m : c.get_members()) {
                                string modifiers;
                                switch (m.get_visibility()) {
                                case VISIBLE_ACCESS:
                                        modifiers += 'v';
                                        break;
                                case HIDDEN_ACCESS:
                                        modifiers += 'h';
                                        break;
                                case CHILD_VISIBLE_ACCESS:
                                        modifiers += 'l';
                                        break;
                                case ASSEMBLY_VISIBLE_ACCESS:
                                        modifiers += 'a';
                                        break;
                                }
                                if (m.is_static())
                                        modifiers += 's';
                                if (m.is_get_set())
                                        modifiers += 'g';
                                cout << "\t\t\t" << m.get_type().to_string() << "[" << modifiers << "] " << m.get_name() << "\n";
                        }
                        cout << "\t\t)\n";
                        cout << "\t\t[\n";
                        for (method m : c.get_methods()) {
                                string modifiers;
                                switch (m.get_visibility()) {
                                case VISIBLE_ACCESS:
                                        modifiers += 'v';
                                        break;
                                case HIDDEN_ACCESS:
                                        modifiers += 'h';
                                        break;
                                case CHILD_VISIBLE_ACCESS:
                                        modifiers += 'l';
                                        break;
                                case ASSEMBLY_VISIBLE_ACCESS:
                                        modifiers += 'a';
                                        break;
                                }
                                if (m.is_static())
                                        modifiers += 's';
                                if (m.is_read_only())
                                        modifiers += 'c';
                                type_hint t = m.get_return_type();
                                cout << "\t\t\t" << t.to_string() << " " << m.get_name() << "[" << modifiers << "]( ";
                                for (auto &arg : m.get_parameters()) {
                                        // parameter modifiers
                                        cout << arg.second.to_string() << ":" << arg.first << " ";
                                }
                                cout << ")\n";
                        }
                        cout << "\t\t]\n";
                }
                cout << "\n";
                // debug properties
                cout << "-Properties:\n";
                for (auto prop : _properties) {
                        cout << "\t" << prop.first << " : " << prop.second + "\n";
                }
                // additional newline
                cout << "\n";
        }
        
        // validate
        validator v;
        string errors = v.validate(_classes);
        if (errors != "") {
                cerr << "FATAL: Errors found during validation:\n";
                cerr << errors;
                exit(2);
        }
}

// for threading langauge implementation of paser::write()
// not a member method
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

        // generate code
        for (unsigned int i=0; i<_langs.size(); i++) {
                threads.push_back(new thread(
                                        write_langauge,
                                        _langs.at(i),
                                        _classes,
                                        _properties,
                                        _io_mutex
                                )
                        );
        }
        for (thread *t : threads) {
                t->join();
        }
}



// private methods
void parser::debug(string str) const
{
        if (_debug_enabled)
                cout << "DEBUG [Line " << _lex->lineno() << "]: " << str << " [token=" << token_text() << "]" << endl;
}

void parser::error(string err) const
{
        cerr << "ERROR [Line " << _lex->lineno() << "]: " << err << endl;
        exit(1);
}

void parser::next_token(bool exit_on_eof /* = true */) {
        _lookahead = _lex->yylex();
        if (exit_on_eof && _lookahead == END_OF_FILE) {
                error("Unexpected end of file.");
        }
}

string parser::token_text() const {
        return _lex->YYText();
}

//
// This is where the magic happens
//
void parser::parse_statement()
{
        
        switch (_lookahead) {
        case PERCENT:
                next_token();
                parse_property();
                break;
        case INDEFINITE_ARTICLE:
                _classes.push_back(parse_type_definition());
                break;
        default:
                // not a valid statement
                error("Unexpected token: " + token_text());
        } 
}

void parser::parse_property()
{
        debug("Parsing property.");

        if (_lookahead != PROPERTY) {
                error("Key-value pair expected after \"%\" token.");
        }
        string property = token_text();
        string key = property.substr(0, property.find('='));
        string value = property.substr(property.find('=')+1);
        // save property
        _properties[key] = value;
        // special propcessing
        if (key == "LANGUAGE") {
                // split on commas
                unsigned int start = 0;
                unsigned int length = 0;
                while ((start+length) < value.size()) {
                        while (value[start + length] != ',' && (start+length) < value.size())
                                length++;

                        string name = value.substr(start, length);
                        if (_debug_enabled)
                                cout << "Found langauge: " << name << endl;
                        // move start and length to after the comma
                        start = start + length + 1;
                        length = 0;
                        // get langauge with this name
                        language *l = language_factory::get_language(name, _io_mutex, _debug_enabled);
                        if (l == 0) {
                                error("Invalid language: " + name);
                        } else {
                                _langs.push_back(l);
                        }
                }
        }
        
        next_token();
        if (_lookahead != SEMICOLON) {
                // not sure if this is possible
                error("Expected semicolon after property value.");
        }
}

class_def parser::parse_type_definition()
{
        debug("Parsing type definition.");
        if (_lookahead != INDEFINITE_ARTICLE) {
                error("Expected indefinite article at token: '" + token_text() + "'.");
        }
        // INDEFINITE_ARTICLE
        next_token();
        if (_lookahead != IDENTIFIER) {
                error("Expected identifier at token: '" + token_text() + "'.");
        }
        // IDENTIFIER
        // add type
        string name = token_text();
        _types.add_type(name);
        class_def c(name);

        next_token();
        parse_definition_list(c);

        return c;
}

void parser::parse_definition_list(class_def& c)
{
        debug("Parsing definition list.");

        parse_definition(c);
        if (_lookahead == PERIOD) {
                // done with this definition
                return;
        }
        if (_lookahead != SEMICOLON) {
                // does not match a rule
                error("Invalid token '" + token_text() + "' following class definition.");
        }
        // SEMICOLON
        next_token();
        if (_lookahead == AND) {
                next_token();
                parse_definition(c);
                // require period after "AND"
                if (_lookahead != PERIOD) {
                        error("Class definition not ended with a period.");
                }
        } else {
                parse_definition_list(c);
        }
}

void parser::parse_definition(class_def& c)
{
        debug("Parsing definition.");

        if (_lookahead == CAN) {
                // CAN
                next_token();
                parse_action_list(c);
        } else if (_lookahead == HAS) {
                // HAS
                next_token();
                parse_attribute_list(c);
        } else if (_lookahead == IS) {
                // IS
                next_token();
                if (_lookahead != INDEFINITE_ARTICLE) {
                        error("Expected indefinite article following 'is', instead found '" + token_text() + "'.");
                }
                // A
                next_token();
                parse_parent_list(c);
        } else {
                error("Invalid type definition.");
        }
}

void parser::parse_parent_list(class_def &c)
{
        type_hint t = parse_type_hint();
        c.add_parent(t);
        if (_lookahead != COMMA) {
                // must be done
                return;
        }
        // COMMA
        parse_parent_list(c);
}

void parser::parse_action_list(class_def& c)
{
        debug("Parsing action list.");

        method m = parse_action();
        c.add_method(m);
        
        if (_lookahead == COMMA) {
                // continue with rest of list
                next_token();
                // IDENTIFIER -- more to list
                parse_action_list(c);
        }
        // no comma, must be done with list
}

method parser::parse_action()
{
        debug("Parsing action.");
        if (_lookahead == STATIC) {
                next_token();
                method m = parse_action();
                m.set_static(true);
                return m;
        }
        if (_lookahead == READ_ONLY) {
                next_token();
                method m = parse_action();
                m.set_read_only(true);
                return m;
        }
        if (_lookahead == VISIBLE) {
                next_token();
                method m = parse_action();
                m.set_visibility(VISIBLE_ACCESS);
                return m;
        }
        if (_lookahead == HIDDEN) {
                next_token();
                method m = parse_action();
                m.set_visibility(HIDDEN_ACCESS);
                return m;
        }
        if (_lookahead == CHILD_VISIBLE) {
                next_token();
                method m = parse_action();
                m.set_visibility(CHILD_VISIBLE_ACCESS);
                return m;
        }
        if (_lookahead == ASSEMBLY_VISIBLE) {
                next_token();
                method m = parse_action();
                m.set_visibility(ASSEMBLY_VISIBLE_ACCESS);
                return m;
        }
        
        type_hint r_type = parse_type_hint();
        if (_lookahead != IDENTIFIER) {
                error("Invalid method definition.");
        }
        method m(r_type, token_text());

        next_token();
        if (_lookahead == L_PAREN) {
                next_token();
                parse_parameter_list(m);
                if (_lookahead != R_PAREN) {
                        error("Expected ')' after parameter list.");
                }
                // R_PAREN
                next_token();
        }
        return m;
}

void parser::parse_parameter_list(method &m)
{
        debug("Parsing parameter list.");
        type_hint t = parse_type_hint();
        if (_lookahead != IDENTIFIER) {
               error("Invalid parameter list, expected identifier at token '" + token_text() + "'."); 
        }
        m.add_parameter(t, token_text());
        next_token();
        if (_lookahead != COMMA) {
                // must be done
                return;
        }
        next_token();
        // COMMA
        if (_lookahead != IDENTIFIER) {
               error("Invalid parameter list, expected identifier at token '" + token_text() + "'."); 
        }
        parse_parameter_list(m);
}

void parser::parse_attribute_list(class_def& c)
{
        debug("Parsing attribute list.");

        member m = parse_attribute();
        c.add_member(m);
        if (_lookahead != COMMA) {
                // must be done
                return;
        }
        // COMMA
        next_token();
        parse_attribute_list(c);
}

member parser::parse_attribute()
{
        debug("Parsing attribute.");

        if (_lookahead == STATIC) {
                next_token();
                member m = parse_attribute();
                m.set_static(true);
                return m;
        }
        if (_lookahead == CONSTANT) {
                next_token();
                member m = parse_attribute();
                m.set_constant(true);
                return m;
        }
        if (_lookahead == VISIBLE) {
                next_token();
                member m = parse_attribute();
                m.set_visibility(VISIBLE_ACCESS);
                return m;
        }
        if (_lookahead == HIDDEN) {
                next_token();
                member m = parse_attribute();
                m.set_visibility(HIDDEN_ACCESS);
                return m;
        }
        if (_lookahead == CHILD_VISIBLE) {
                next_token();
                member m = parse_attribute();
                m.set_visibility(CHILD_VISIBLE_ACCESS);
                return m;
        }
        if (_lookahead == ASSEMBLY_VISIBLE) {
                next_token();
                member m = parse_attribute();
                m.set_visibility(ASSEMBLY_VISIBLE_ACCESS);
                return m;
        }

        if (_lookahead == GETTER) {
                next_token();
                member m = parse_attribute();
                m.set_getter(true);
                return m;
        }
        else if (_lookahead == SETTER) {
                next_token();
                member m = parse_attribute();
                m.set_setter(true);
                return m;
        }
        else if (_lookahead == GET_SET) {
                next_token();
                member m = parse_attribute();
                m.set_get_set(true);
                return m;
        }

        type_hint t = parse_type_hint();
        if (_lookahead != IDENTIFIER) {
                error("Invalid attribute name: '" + token_text() + "'.");
        }
        member m(t, token_text());

        next_token();
        return m;
}

type_hint parser::parse_type_hint()
{
        if (_lookahead != IDENTIFIER) {
                error("Invalid type name: " + token_text() + ".");
        }
        string name = token_text();
        if (!_types.is_defined(name)) {
                error("Invalid type: '" + name + "'.");
        }
        next_token();
        vector<type_hint> generics;
        if (_lookahead == L_BRACKET) {
                if (!_types.is_generic(name)) {
                        error("Type '" + name + "' is not generic.");
                }
                next_token();
                generics = parse_generic_type_list();
                if (_lookahead != R_BRACKET) {
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
        if (_lookahead != COMMA) {
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
