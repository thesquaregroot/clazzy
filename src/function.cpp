
#include "h/function.h"
#include "h/type_hint.h"
#include <map>
#include <string>
using namespace cranberry;
using namespace std;

// string name
// type_hint return_type
// map<string, type_hint> params

function::function(type_hint returns, string name)
{
        return_type = returns;
        this->name = name;
}

string function::get_name() const
{
        return name;
}

type_hint function::get_return_type() const
{
        return return_type;
}

void function::add_parameter(type_hint type, string p)
{
        params[p] = type;
}

map<string, type_hint> function::get_parameters() const
{
        return params;
}
