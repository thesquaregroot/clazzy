
// for parsing
#include "parser.h"
#include "class_def.h"
#include "method.h"
#include "member.h"
#include "token.h"
#include "language.h"
#include "lang_c.h"
#include "lang_cpp.h"
#include "lang_java.h"
#include "lang_python.h"
#include "type_hint.h"
#include "access_type.h"
#include "validator.h"
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

const unsigned int parser::LANG_C = 1;
const unsigned int parser::LANG_CPP = 2;
const unsigned int parser::LANG_JAVA = 4;
const unsigned int parser::LANG_PYTHON = 8;

parser::parser(FlexLexer *lexer)
{
    _lex = lexer;
    _io_mutex = new mutex();
}

parser::~parser()
{
    if (_io_mutex != nullptr) {
        delete _io_mutex;
    }
}

void parser::set_debug(bool debug_enabled)
{
    _debug_enabled = debug_enabled;
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
        for (const class_def c : _classes) {
            cout << "\t" << c.get_name() << "\n";
            for (design_pattern d : c.get_design_patterns()) {
                for (auto it = design_pattern_map.cbegin(); it != design_pattern_map.cend(); it++) {
                    if (d == it->second) {
                        cout << "\t\t-- @" << it->first << "\n";
                    }
                }
            }
            for (type_hint p : c.get_parents()) {
                cout << "\t\t-- " << p.to_string() << "\n";
            }
            cout << "\t\t(\n";
            for (constructor ctor : c.get_constructors()) {
                string modifiers;
                switch (ctor.get_visibility()) {
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
                cout << "\t\t\t" << c.get_name() << "[" << modifiers << "]";
                print_arguments(&ctor);
                cout << endl;
            }
            if (c.has_explicit_destructor()) {
                string modifiers;
                access_type *at = c.get_destructor_visibility();
                if (at != nullptr) {
                    switch (*at) {
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
                }
                cout << "\t\t\t" << "~" << c.get_name();
                if (modifiers != "") {
                    cout << "[" << modifiers << "]";
                }
                cout << "()" << endl;
            }
            cout << endl;
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
                if (m.has_get_set())
                    modifiers += 'g';
                cout << "\t\t\t" << m.get_type().to_string() << " " << m.get_name() << "[" << modifiers << "]" << endl;
            }
            cout << "\t\t)" << endl;
            cout << "\t\t[" << endl;
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
                cout << "\t\t\t" << t.to_string() << " " << m.get_name() << "[" << modifiers << "]";
                print_arguments(&m);
                cout << endl;
            }
            cout << "\t\t]" << endl;
        }
        cout << "\n";
        // debug properties
        cout << "-Properties:\n";
        for (auto prop : _properties) {
            cout << "\t" << prop.first << " : " << prop.second  << endl;
        }
        // additional newline
        cout << endl;
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
// private static method
void parser::write_langauge(
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

void parser::write(unsigned int languages) const
{
    // write all language files
    vector<thread*> threads;
    vector<language*> langs;
    // find set languages
    if (languages & LANG_C) {
        langs.push_back(new lang_c(_io_mutex, _debug_enabled));
    }
    if (languages & LANG_CPP) {
        langs.push_back(new lang_cpp(_io_mutex, _debug_enabled));
    }
    if (languages & LANG_JAVA) {
        langs.push_back(new lang_java(_io_mutex, _debug_enabled));
    }
    if (languages & LANG_PYTHON) {
        langs.push_back(new lang_python(_io_mutex, _debug_enabled));
    }
    // create threads for each language
    for (size_t i=0; i<langs.size(); i++) {
        threads.push_back(new thread(
                    write_langauge,
                    langs.at(i),
                    _classes,
                    _properties,
                    _io_mutex
                )
            );
    }
    // join and cleanup threads
    for (thread* t : threads) {
        t->join();
        delete t;
    }
    // cleanup languages
    for (language* lang : langs) {
        delete lang;
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
    debug("Parsing parent list.");

    parse_parent(c);
    if (_lookahead != COMMA) {
        // must be done
        return;
    }
    // COMMA
    next_token();
    parse_parent_list(c);
}

void parser::parse_parent(class_def &c)
{
    debug("Parsing parent.");
    if (_lookahead == AT_SYMBOL) {
        next_token();
        c.add_design_pattern(design_pattern_map[token_text()]);
        next_token();
    } else {
        type_hint t = parse_type_hint();
        c.add_parent(t);
    }
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
    if (is_access_type(_lookahead)) {
        access_type at = get_access_type(_lookahead);
        next_token();
        method m = parse_action();
        m.set_visibility(at);
        return m;
    }
    
    type_hint r_type = parse_type_hint();
    if (_lookahead != IDENTIFIER) {
        error("Invalid method definition.");
    }
    method m(r_type, token_text());

    next_token();
    if (_lookahead == L_PAREN) {
        parse_parameters(&m);
    }
    return m;
}

void parser::parse_parameters(parameterized * const m)
{
    debug("Parsing parameters.");
    if (_lookahead != L_PAREN) {
        error("Parameter list must start with '(' token.");
    }
    // L_PAREN
    next_token();
    if (_lookahead == R_PAREN) {
        // R_PAREN
        next_token();
        return;
    }
    // not R_PAREN (must have parameters)
    parse_parameter_list(m);
    if (_lookahead != R_PAREN) {
        error("Expected ')' token after parameter list.");
    }
    // R_PAREN
    next_token();
}

void parser::parse_parameter_list(parameterized * const m)
{
    debug("Parsing parameter list.");
    type_hint t = parse_type_hint();
    if (_lookahead != IDENTIFIER) {
           error("Invalid parameter list, expected identifier at token '" + token_text() + "'."); 
    }
    m->add_parameter(t, token_text());
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

    parse_attribute(c);

    if (_lookahead != COMMA) {
        // must be done
        return;
    }
    // COMMA
    next_token();
    parse_attribute_list(c);
}

void parser::parse_attribute(class_def& c)
{
    debug("Parsing attribute.");

    access_type *at = nullptr;
    while (is_access_type(_lookahead)) {
        // deleted at end of method
        at = new access_type(get_access_type(_lookahead));
        next_token();
    }
    // have optional access_type
    if (_lookahead == CONSTRUCTOR) {
        constructor ctor = parse_constructor();
        if (at != nullptr) {
            ctor.set_visibility(*at);
        }
        c.add_constructor(ctor);
    } else if (_lookahead == DESTRUCTOR) {
        c.set_explicit_destructor(true, at);
        next_token();
        // option parens
        if (_lookahead == L_PAREN) {
            // L_PAREN
            next_token();
            if (_lookahead != R_PAREN) {
                error("Destructors should not accept arguments.");
            }
            // R_PAREN
            next_token();
        }
    } else {
        member m = parse_member();
        if (at != nullptr) {
            m.set_visibility(*at);
        }
        // additional member processing
        if (_lookahead == WITH) {
            next_token();
            if (_lookahead == GETTER) {
                m.set_getter(true);
            }
            else if (_lookahead == SETTER) {
                m.set_setter(true);
            }
            else if (_lookahead == GET_SET) {
                m.set_get_set(true);
            }
            next_token();
        }
        c.add_member(m);
    }
    delete at;
}

constructor parser::parse_constructor()
{
    debug("Parsing constructor.");
    // CONSTRUCTOR
    next_token();
    constructor c;
    parse_parameters(&c);
    return c;
}

member parser::parse_member()
{
    debug("Parsing member.");
    if (_lookahead == STATIC) {
        next_token();
        member m = parse_member();
        m.set_static(true);
        return m;
    }
    if (_lookahead == CONSTANT) {
        next_token();
        member m = parse_member();
        m.set_read_only(true);
        return m;
    }

    type_hint t = parse_type_hint();
    if (_lookahead != IDENTIFIER) {
        error("Invalid member name: '" + token_text() + "'.");
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

void parser::print_arguments(parameterized * const c) const {
    cout << "( ";
    for (auto &arg : c->get_parameters()) {
        // parameter modifiers
        cout << arg.second.to_string() << ":" << arg.first << " ";
    }
    cout << ")";
}

bool parser::is_access_type(const int token) const
{
    return (token == VISIBLE
        || token == HIDDEN
        || token == CHILD_VISIBLE
        || token == ASSEMBLY_VISIBLE);
}

access_type parser::get_access_type(const int token) const
{
    switch (token) {
    case VISIBLE:       return VISIBLE_ACCESS;
    case HIDDEN:        return HIDDEN_ACCESS;
    case CHILD_VISIBLE:     return CHILD_VISIBLE_ACCESS;
    case ASSEMBLY_VISIBLE:  return ASSEMBLY_VISIBLE_ACCESS;
    }
    // this should never actually happen
    // but we TECHNICALLY need a catch-all
    return VISIBLE_ACCESS;
}

