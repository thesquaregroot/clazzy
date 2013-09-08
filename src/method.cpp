
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

method::method(const method& original) {
    _return_type = original._return_type;
    _name = original._name;
    _params = original._params;
    _is_static = original._is_static;
    _is_read_only = original._is_read_only;
    _visibility = original._visibility;

    if (original._getter_member != nullptr) _getter_member = new member(*original._getter_member);
    if (original._setter_member != nullptr) _setter_member = new member(*original._setter_member);
}

method::~method() {
    if (_getter_member != nullptr) delete _getter_member;
    if (_setter_member != nullptr) delete _setter_member;
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

bool method::is_getter() const
{
    return (_getter_member != nullptr && _getter_member->has_getter());
}

void method::set_getter(const bool val, const member* const m)
{
    if (val) {
        if (m != nullptr)
            _getter_member = new member(*m);
    }
    else {
        if (_getter_member != nullptr) delete _getter_member;
        _getter_member = nullptr;
    }

    if (_getter_member != nullptr)
        _getter_member->set_getter(val);
}

bool method::is_setter() const
{
    return (_setter_member != nullptr && _setter_member->has_setter());
}

void method::set_setter(bool val, const member* const m)
{
    if (val) {
        if (m != nullptr) {
            _setter_member = new member(*m);
        }
    }
    else {
        if (_setter_member != nullptr) delete _setter_member;
        _setter_member = nullptr;
    }

    if (_setter_member != nullptr)
        _setter_member->set_setter(val);
}

const member* method::get_getter_member() const {
    return _getter_member;
}

const member* method::get_setter_member() const {
    return _setter_member;
}

