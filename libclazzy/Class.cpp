
#include "Class.h"
using namespace clazzy;
using std::string;
using std::vector;


Class::Class(const string& name) {
    _name = name;
}

//// High Level Definition
string Class::get_name() const {
    return _name;
}

void Class::set_name(const string& name) {
    _name = name;
}

vector<Type> Class::get_parents() const {
    return _parents;
}

void Class::add_parent(const Type& parent) {
    _parents.push_back(parent);
}

vector<DesignPattern> Class::get_design_patterns() const {
    return _design_patterns;
}

void Class::add_design_pattern(const DesignPattern& pattern) {
    _design_patterns.push_back(pattern);
}

// returns true iff there is an abstract method present
bool Class::is_abstract() const {
    for (const Method& m : _methods) {
        if (m.is_abstract()) {
            return true;
        }
    }
    return false;
}

// returns true iff there are no:
//   - non-static members
//   - non-abstract methods
//   - constructors or destructors
bool Class::is_interface() const {
    // check for non-abstract methods
    for (const Method& m : _methods) {
        if (!m.is_abstract()) {
            // not abstract, even if this is a constructor/destructor, we should still fail.
            return false;
        }
    }
    // check for non-static members
    for (const Member& m : _members) {
        if (!m.is_static()) {
            return false;
        }
    }
    // everything checks out
    return true;
}

int Class::get_generics_count() const {
    return _generics_count;
}

void Class::set_generics_count(int count) {
    _generics_count = count;
}

//// Access
bool Class::is_final() const {
    return _is_final;
}

void Class::set_final(bool value) {
    _is_final = value;
}

AccessLevel Class::get_access_level() const {
    return _access_level;
}

void Class::set_access_level(const AccessLevel& level) {
    _access_level = level;
}

//// Namespaces and Packages
string Class::get_namespace() const {
    return _namespace;
}

void Class::set_namespace(const string& value) {
    _namespace = value;
}

string Class::get_package() const {
    return _package;
}

void Class::set_package(const string& value) {
    _package = value;
}

//// Methods and Members
vector<Method> Class::get_methods() const {
    return _methods;
}

void Class::add_method(const Method& method) {
    _methods.push_back(method);
}

vector<Member> Class::get_members() const {
    return _members;
}

void Class::add_member(const Member& member) {
    _members.push_back(member);
}

//// Documentation methods
string Class::get_doc_short() const {
    return _doc_short;
}

void Class::set_doc_short(const string& value) {
    _doc_short = value;
}

string Class::get_doc_detail() const {
    return _doc_detail;
}

void Class::set_doc_detail(const string& value) {
    _doc_detail = value;
}

