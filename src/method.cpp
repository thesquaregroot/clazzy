
#include "h/method.h"
#include "h/type_hint.h"
#include <map>
#include <string>
using namespace clazzy;
using namespace std;

// string _name
// type_hint _return_type
// bool _is_static
// bool _is_read_only
// member *_getter_member
// member *_setter_member

method::method(type_hint returns, string name)
{
        _return_type = returns;
        _name = name;
}

method::method(const method& original)
{
        _return_type = original._return_type;
        _name = original._name;
        // copy parameters
        for (auto param : original.get_parameters()) {
                add_parameter(param.second, param.first);
        }
        _is_static = original._is_static;
        _is_read_only = original._is_read_only;
        // copy visibility
        set_visibility(original.get_visibility());

        if (original._getter_member != nullptr) _getter_member = new member(*original._getter_member);
        if (original._setter_member != nullptr) _setter_member = new member(*original._setter_member);
}

method::~method()
{
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

// modifiers
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

// getter-setter methods
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

