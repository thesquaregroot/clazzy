
#include "Method.h"
using namespace clazzy;
using std::string;
using std::vector;


Method::Method(const string& name) {
    _name = name;
}

//// High Level Definition
string Method::get_name() const {
    return _name;
}

void Method::set_name(const string& name) {
    _name = name;
}

//// Access
bool Method::is_abstract() const {
    return _is_abstract;
}

void Method::set_abstract(bool value) {
    _is_abstract = value;
}

bool Method::is_static() const {
    return _is_static;
}

void Method::set_static(bool value) {
    _is_static = value;
}

bool Method::is_read_only() const {
    return _is_read_only;
}

void Method::set_read_only(bool value) {
    _is_read_only = value;
}

bool Method::is_final() const {
    return _is_final;
}

void Method::set_final(bool value) {
    _is_final = value;
}

AccessLevel Method::get_access_level() const {
    return _access_level;
}

void Method::set_access_level(const AccessLevel& level) {
    _access_level = level;
}

//// Arguments and Return Type
vector<Argument> Method::get_arguments() const {
    return _arguments;
}

void Method::add_argument(const Argument& argument) {
    _arguments.push_back(argument);
}

Type Method::get_return_type() const {
    return _return_type;
}

void Method::set_return_type(const Type& type) {
    _return_type = type;
}

//// Documentation methods
string Method::get_doc_short() const {
    return _doc_short;
}

void Method::set_doc_short(const string& value) {
    _doc_short = value;
}

string Method::get_doc_detail() const {
    return _doc_detail;
}
void Method::set_doc_detail(const string& value) {
    _doc_detail = value;
}

