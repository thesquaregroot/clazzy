
#include "h/parser.h"
#include "h/language.h"
#include "h/class_def.h"
#include <FlexLexer.h>
#include <vector>
using namespace std;

// FlexLexer *lex
// vector<class_def> classes
// vector<langauge> langs

parser::parser(FlexLexer *lexer)
{
    lex = lexer;
}

parser::~parser()
{
    delete lex;
}

void parser::parse()
{
    // TODO
}

void parser::write() const
{
    // write all language files
    for (unsigned int i=0; i<langs.size(); i++) {
        const language *lang = &langs.at(i);
        cout << "Building " << lang->get_name() << " code..." << endl;
        lang->create(classes);
    }
}
