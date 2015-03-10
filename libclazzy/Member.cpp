
#include "Member.h"
using namespace clazzy;
using std::string;
using std::vector;


Member::Member(const Type& type, const string& name) {
    _type = type;
    _name = name;
}

//// High Level Definition
string Member::get_name() const {
    return _name;
}

void Member::set_name(const string& name) {
    _name = name;
}

//// Access
bool Member::is_static() const {
    return _is_static;
}

void Member::set_static(bool value) {
    _is_static = value;
}

bool Member::is_read_only() const {
    return _is_read_only;
}

void Member::set_read_only(bool value) {
    _is_read_only = value;
}

bool Member::is_final() const {
    return _is_final;
}

void Member::set_final(bool value) {
    _is_final = value;
}

AccessLevel Member::get_access_level() const {
    return _access_level;
}
void Member::set_access_level(const AccessLevel& level) {
    _access_level = level;
}

//// Type
Type Member::get_type() const {
    return _type;
}

void Member::set_type(const Type& type) {
    _type = type;
}

string Member::get_default_value() const {
    return _default_value;
}

void Member::set_default_value(const string& value) {
    _default_value = value;
}

//// Documentation methods
string Member::get_doc_short() const {
    return _doc_short;
}

void Member::set_doc_short(const string& value) {
    _doc_short = value;
}

string Member::get_doc_detail() const {
    return _doc_detail;
}

void Member::set_doc_detail(const string& value) {
    _doc_detail = value;
}

