
#include "h/member.h"
#include <string>
using namespace clazzy;
using namespace std;

// string _name
// type_hint _type
// bool _is_static
// bool _is_reference


member::member(const type_hint &type, const string& name)
{
        _type = type;
        _name = name;
}

string member::get_name() const
{
        return _name;
}

type_hint member::get_type() const
{
        return _type;
}

bool member::is_static() const
{
        return _is_static;
}

void member::set_static(const bool &val)
{
        _is_static = val;
}

bool member::is_constant() const
{
        return _is_constant;
}

void member::set_constant(const bool &val)
{
        _is_constant = val;
}

access_type member::get_visibility() const
{
        return _visibility;
}

void member::set_visibility(const access_type &val)
{
        _visibility = val;
}

