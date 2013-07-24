
#include "h/member.h"
#include <string>
using namespace cranberry;
using namespace std;

// string _name
// type_hint _type
// bool _is_constant
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

bool member::is_constant() const
{
        return _is_constant;
}

void member::set_constant(const bool &val)
{
        _is_constant = val;
}

bool member::is_reference() const
{
        return _is_reference;
}

void member::set_reference(const bool &val)
{
        _is_reference = val;
}

