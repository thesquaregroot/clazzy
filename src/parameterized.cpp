#include "h/parameterized.h"
using namespace clazzy;
using namespace std;

// map<string, type_hint> _params

void parameterized::add_parameter(const type_hint &type, const string &p)
{
        _params[p] = type;
}

map<string, type_hint> parameterized::get_parameters() const
{
        return _params;
}

