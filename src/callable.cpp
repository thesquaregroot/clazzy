
#include "h/callable.h"
using namespace clazzy;
using namespace std;

// map<string, type_hint> _params

void callable::add_parameter(type_hint type, string p)
{
        _params[p] = type;
}

map<string, type_hint> callable::get_parameters() const
{
        return _params;
}

