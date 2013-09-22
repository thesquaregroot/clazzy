
#include "h/class_def.h"
#include <iostream>
#include <string>
#include <vector>
using namespace clazzy;
using namespace std;

// string _name
// map<access_type,vector<constructor> _ctors;
// bool _has_destructor
// access_type *_destructor_access
// map<access_type,vector<method>> _methods
// map<access_type,vector<member>> _members
// vector<type_hint> _parents
// vector<type_hint _referenced_types
// vector<design_pattern> _design_patterns

class_def::class_def(const string& name)
{
        _name = name;
}

class_def::class_def(const class_def &c)
{
        _name = c._name;
        _ctors = c._ctors;
        _has_destructor = c._has_destructor;
        if (c._destructor_access != nullptr) {
                _destructor_access = new access_type(*c._destructor_access);
        } else {
                _destructor_access = nullptr;
        }
        _methods = c._methods;
        _members = c._members;
        _parents = c._parents;
        _referenced_types = c._referenced_types;
        _design_patterns = c._design_patterns;
}

class_def::~class_def() {
        delete _destructor_access;
        _destructor_access = nullptr;
}

void class_def::set_name(const string& name)
{
        _name = name;
}

string class_def::get_name() const
{
        return _name;
}

void class_def::add_constructor(constructor &c)
{
        _ctors[c.get_visibility()].push_back(c);
}

void class_def::set_explicit_destructor(const bool b, const access_type * visibility)
{
        _has_destructor = b;
        if (visibility != nullptr && b) {
                _destructor_access = new access_type(*visibility);
        } else {
                delete _destructor_access;
                _destructor_access = nullptr;
        }
}

void class_def::add_method(method &m)
{
        _methods[m.get_visibility()].push_back(m);
}

void class_def::add_member(member &m)
{
        if (m.has_setter()) {
            method setter(m.get_type(), "set_"+m.get_name());
            setter.set_setter(true, &m);
            setter.add_parameter(m.get_type(), "value"); // name setter parameter "value", since it could be anything
            this->add_method(setter);
        }
        if (m.has_getter()) {
            method getter(m.get_type(), "get_"+m.get_name());
            getter.set_getter(true, &m);
            this->add_method(getter);
        }

        _members[m.get_visibility()].push_back(m);
}

void class_def::add_parent(type_hint &t)
{
        _parents.push_back(t);
}

void class_def::add_design_pattern(design_pattern &d)
{
        _design_patterns.push_back(d);
}

void class_def::set_referenced_types(const vector<type_hint> &types)
{
        _referenced_types = types;
}

vector<constructor> class_def::get_constructors(const access_type *visibility) const
{
        return get<constructor>(_ctors, visibility);
}

bool class_def::has_explicit_destructor() const
{
        return _has_destructor;
}

access_type *class_def::get_destructor_visibility() const
{
        return _destructor_access;
}

vector<method> class_def::get_methods(const access_type *visibility) const
{
        return get<method>(_methods, visibility);
}

vector<member> class_def::get_members(const access_type *visibility) const
{
        return get<member>(_members, visibility);
}

vector<type_hint> class_def::get_parents() const
{
        return _parents;
}

vector<type_hint> class_def::get_referenced_types() const
{
        return _referenced_types;
}

vector<design_pattern> class_def::get_design_patterns() const
{
        return _design_patterns;
}

template<class T>
vector<T> class_def::get(const map<access_type,vector<T>> &m, const access_type *visibility) const {
        if (visibility != nullptr) {
                // return members with given visibilty
                auto it = m.find(*visibility);
                if (it != m.end()) {
                        return it->second;
                }
                return vector<T>();
        }
        // return all members
        vector<T> all;
        for (auto p : m) {
                for (T t : p.second) {
                        all.push_back(t);
                }
        }
        return all;
}

