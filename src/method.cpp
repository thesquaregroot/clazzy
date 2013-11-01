
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
// member *_member

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

        if (original._member != nullptr) _member = new member(*original._member);
        _is_getter = original._is_getter;
}

method::~method()
{
    if (_member != nullptr) delete _member;
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

void method::set_static(const bool val)
{
        _is_static = val;
}

bool method::is_read_only() const
{
        return _is_read_only;
}

void method::set_read_only(const bool val)
{
        _is_read_only = val;
}

// getter-setter methods
bool method::is_getter() const
{
        return (_member != nullptr && _is_getter);
}

void method::set_getter(const member* const m)
{
        set_member(true, m);
}

bool method::is_setter() const
{
        return (_member != nullptr && !_is_getter);
}

void method::set_setter(const member* const m)
{
        set_member(false, m);
}

const member* method::get_member() const {
        return _member;
}

void method::set_member(bool getter, const member* const m) {
        if (m != nullptr) {
                // copy member locally
                _member = new member(*m);
                _is_getter = getter;
        } else {
                // null passed, if this is the appropriate type, remove the underlying member
                if (_is_getter == getter) {
                        if (_member != nullptr) {
                                delete _member;
                                _member = nullptr;
                        }
                }
        }
}
