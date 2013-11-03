
#include "h/member.h"
#include <string>
using namespace clazzy;
using namespace std;

// string _name
// type_hint _type
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

void member::set_constant(const bool val)
{
        _is_constant = val;
}

bool member::has_get_set() const
{
        return (_getter_setter & 0x03);
}

void member::set_get_set(bool val)
{
        if (val)
            _getter_setter |= 0x03;
        else
            _getter_setter &= 0x03^0xFF;
}

bool member::has_getter() const
{
        return (_getter_setter & 0x01);
}

void member::set_getter(bool val)
{
        if (val) 
            _getter_setter |= 0x01;
        else
            _getter_setter &= 0x01^0xFF;
}

bool member::has_setter() const
{
        return (_getter_setter & 0x02);
}

void member::set_setter(bool val)
{
        if (val)
            _getter_setter |= 0x02;
        else
            _getter_setter &= 0x02^0xFF;
}

