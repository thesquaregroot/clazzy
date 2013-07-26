
#include "h/member.h"
#include <string>
using namespace cranberry;
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

