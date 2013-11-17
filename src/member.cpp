
#include "h/member.h"
#include <string>
using namespace clazzy;
using namespace std;

// string _name
// type_hint _type
// string _getter_name
// string _setter_name

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

bool member::has_get_set() const
{
        return (_getter_setter & _BOTH);
}

void member::set_get_set(bool val, const string &getter_name, const string &setter_name)
{
        if (val) {
                _getter_setter = _BOTH;
                set_getter_name(getter_name);
                set_setter_name(setter_name);
        } else {
                _getter_setter = _NEITHER;
        }
}

bool member::has_getter() const
{
        return (_getter_setter & _GETTER);
}

string member::get_getter_name() const
{
        return _getter_name;
}

void member::set_getter(bool val, const string &name)
{
        if (val) {
                _getter_setter |= _GETTER;
                set_getter_name(name);
        } else {
                _getter_setter &= _GETTER^0xFF;
        }
}

bool member::has_setter() const
{
        return (_getter_setter & _SETTER);
}

string member::get_setter_name() const
{
        return _setter_name;
}

void member::set_setter(bool val, const string &name)
{
        if (val) {
                _getter_setter |= _SETTER;
                set_setter_name(name);
        } else {
                _getter_setter &= _SETTER^0xFF;
        }
}

bool member::is_initialized() const
{
        return _is_initialized;
}

void member::set_initialized(const bool val)
{
        _is_initialized = val;
}

void member::set_getter_name(const string& name)
{
        if (name != "") {
                _getter_name = name;
        } else {
                _getter_name = "get_" + _name;
        }
}

void member::set_setter_name(const string& name)
{
        if (name != "") {
                _setter_name = name;
        } else {
                _setter_name = "set_" + _name;
        }
}

