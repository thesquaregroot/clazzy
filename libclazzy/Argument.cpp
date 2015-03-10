
#include "Argument.h"
using namespace clazzy;
using std::string;
using std::vector;

Argument::Argument(const string& name) {
    _name = name;
}

string Argument::get_name() const {
    return _name;
}

void Argument::set_name(const string& name) {
    _name = name;
}

Type Argument::get_type() const {
    return _type;
}

void Argument::set_type(const Type& type) {
    _type = type;
}

bool Argument::is_read_only() const {
    return _is_read_only;
}

void Argument::set_read_only(bool value) {
    _is_read_only = value;
}

string Argument::get_default_value() const {
    return _default_value;
}
void Argument::set_default_value(const string& value) {
    _default_value = value;
}

