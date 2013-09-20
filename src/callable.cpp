
#include "h/callable.h"
using namespace clazzy;
using namespace std;

// access_type _visibility
// map<string, type_hint> _params

void callable::add_parameter(type_hint type, string p)
{
        _params[p] = type;
}

map<string, type_hint> callable::get_parameters() const
{
        return _params;
}

access_type callable::get_visibility() const
{
        return _visibility;
}

void callable::set_visibility(const access_type &val)
{
        _visibility = val;
}

