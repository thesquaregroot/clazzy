
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
        {VISIBLE_ACCESS, ""},
        {HIDDEN_ACCESS, ""},
        {CHILD_VISIBLE_ACCESS, ""},
        {ASSEMBLY_VISIBLE_ACCESS, ""}
};

string lang_c::get_name() const
{
        return "C";
}

string lang_c::get_simple_name() const
{
        return "c";
}

void lang_c::initialize()
{
        // create mappings and add any additional
        types.add_type("byte", "char");
        types.add_type("short", "short");
        types.add_type("integer", "int");
        types.add_type("long", "long");
        types.add_type("character", "char");
        types.add_type("string", "char *");
        types.add_type("float", "float");
        types.add_type("double", "double");
        types.add_type("boolean", "bool");
        types.add_type("void", "void");
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

string lang_c::write_header(string base_dir, class_def &c) const
{
        
}

void lang_c::write_source(string base_dir, class_def &c, string header_file) const
{
        
}
