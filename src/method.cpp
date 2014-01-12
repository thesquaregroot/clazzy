
#include "method.h"
#include <map>
#include <string>
using namespace clazzy;
using namespace std;

// string _name
// type_hint _return_type
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

        // copy inherited values
        // from parameterized
        for (auto param : original.get_parameters()) {
                add_parameter(param.second, param.first);
        }
        // from class_component
        set_visibility(original.get_visibility());
        set_static(original.is_static());
        set_read_only(original.is_read_only());

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
