
#include "h/lang_python.h"
#include "h/class_def.h"
#include "h/method.h"
#include "h/member.h"
#include <vector>
#include <map>
#include <string>
#include <mutex>
using namespace clazzy;
using namespace std;

map<access_type,string> lang_python::access_prefixes = {
        // TODO: create mappings
        {VISIBLE_ACCESS, ""},
        {HIDDEN_ACCESS, ""},
        {CHILD_VISIBLE_ACCESS, ""},
        {ASSEMBLY_VISIBLE_ACCESS, ""}
};

string lang_python::get_name() const
{
        return "Python";
}

void lang_python::initialize()
{
        // TODO: create mappings and add any additional
        types.add_type("byte", "");
        types.add_type("short", "");
        types.add_type("integer", "");
        types.add_type("long", "");
        types.add_type("character", "");
        types.add_type("string", "");
        types.add_type("float", "");
        types.add_type("double", "");
        types.add_type("boolean", "");
        types.add_type("void", "");
}

void lang_python::create(
                        const vector<class_def> &classes,
                        const map<string,string> &properties
        ) const
{
        // TODO: Implement code generation
}

