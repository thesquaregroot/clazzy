
#include "h/lang_c.h"
#include "h/class_def.h"
#include "h/method.h"
#include "h/member.h"
#include <vector>
#include <map>
#include <string>
#include <mutex>
using namespace clazzy;
using namespace std;

map<access_type,string> lang_c::access_prefixes = {
        // TODO: create mappings
        {VISIBLE_ACCESS, ""},
        {HIDDEN_ACCESS, ""},
        {CHILD_VISIBLE_ACCESS, ""},
        {ASSEMBLY_VISIBLE_ACCESS, ""}
};

string lang_c::get_name() const
{
        return "C";
}

void lang_c::initialize()
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
        // container types
        types.add_type("array", "");
        types.add_type("deque", "");
        types.add_type("list", "");
        types.add_type("set", "");
        types.add_type("stack", "");
        types.add_type("queue", "");
        types.add_type("map", "");
        types.add_type("pointer", "");
}

void lang_c::create(
                        const vector<class_def>& /* classes: not yet used */,
                        const map<string,string>& /* properties: not used */
        ) const
{
        // TODO: Implement code generation
}

