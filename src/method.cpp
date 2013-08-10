
#include "h/method.h"
#include "h/type_hint.h"
#include <map>
#include <string>
using namespace clazzy;
using namespace std;

// string name
// type_hint return_type
// map<string, type_hint> params

method::method(type_hint returns, string name)
{
        _return_type = returns;
        _name = name;
}

string method::get_name() const
{
        return _name;
}

type_hint method::get_return_type() const
{
        return _return_type;
}

void method::add_parameter(type_hint type, string p)
{
        _params[p] = type;
}

map<string, type_hint> method::get_parameters() const
{
        return _params;
}

bool method::is_static() const
{
        return _is_static;
}

void method::set_static(const bool &val)
{
        _is_static = val;
}

bool method::is_read_only() const
{
        return _is_read_only;
}

void method::set_read_only(const bool &val)
{
        _is_read_only = val;
}

access_type method::get_visibility() const
{
        return _visibility;
}

void method::set_visibility(const access_type &val)
{
        _visibility = val;
}

