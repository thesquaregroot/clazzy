
#include "type_util.h"
#include "type.h"
using namespace clazzy;
using namespace std;

// initialize private maps
const std::map<std::string,type> type_util::generics = {
    {"array", ARRAY},
    {"ARRAY", ARRAY},
    {"deque", DEQUE},
    {"DEQUE", DEQUE},
    {"list", LIST},
    {"LIST", LIST},
    {"set", SET},
    {"SET", SET},
    {"stack", STACK},
    {"STACK", STACK},
    {"queue", QUEUE},
    {"QUEUE", QUEUE},
    {"map", MAP},
    {"MAP", MAP},
    {"pointer", POINTER},
    {"POINTER", POINTER}
};
const std::map<std::string,type> type_util::primitives = {
    {"byte", BYTE},
    {"BYTE", BYTE},
    {"short", SHORT},
    {"SHORT", SHORT},
    {"integer", INTEGER},
    {"INTEGER", INTEGER},
    {"long", LONG},
    {"LONG", LONG},
    {"character", CHARACTER},
    {"CHARACTER", CHARACTER},
    {"string", STRING},
    {"STRING", STRING},
    {"float", FLOAT},
    {"FLOAT", FLOAT},
    {"double", DOUBLE},
    {"DOUBLE", DOUBLE},
    {"boolean", BOOLEAN},
    {"BOOLEAN", BOOLEAN},
    {"void", VOID},
    {"VOID", VOID}
};
// set<string> user_types;


bool type_util::add_type(const std::string &name)
{
    if (user_types.count(name) > 0) {
        return false;
    }
    user_types.insert(name);
    return true;
}

bool type_util::is_defined(const std::string &name) const
{
    return is_user_type(name) || is_primitive(name) || is_generic(name);
}

bool type_util::is_generic(const std::string &name) const
{
    return generics.count(name) > 0;
}

bool type_util::is_primitive(const std::string &name) const
{
    return primitives.count(name) > 0;
}

bool type_util::is_user_type(const std::string &name) const
{
    return user_types.count(name) > 0;
}

