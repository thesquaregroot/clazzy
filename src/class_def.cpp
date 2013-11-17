
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

const char * class_def::SETTER_PARAMETER_NAME = "value";

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

class_def::class_def(class_def &&c)
{
        _name = c._name;
        _ctors = std::move(c._ctors);
        _has_destructor = c._has_destructor;
        if (c._destructor_access != nullptr) {
                // steal pointer location
                _destructor_access = c._destructor_access;
                // remove temporary class_def's memory of this pointer
                c._destructor_access = nullptr;
        } else {
                _destructor_access = nullptr;
        }
        _methods = std::move(c._methods);
        _members = std::move(c._members);
        _parents = std::move(c._parents);
        _referenced_types = std::move(c._referenced_types);
        _design_patterns = std::move(c._design_patterns);
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

void class_def::add_constructor(const constructor &c)
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

void class_def::add_method(const method &m)
{
        _methods[m.get_visibility()].push_back(m);
}

void class_def::add_member(const member &m)
{
        if (m.has_setter()) {
                method setter(m.get_type(), m.get_setter_name());
                setter.set_setter(&m);
                // name setter parameter "value", since it could be anything
                setter.add_parameter(m.get_type(), class_def::SETTER_PARAMETER_NAME);
                this->add_method(setter);
        }
        if (m.has_getter()) {
                method getter(m.get_type(), m.get_getter_name());
                getter.set_getter(&m);
                this->add_method(getter);
        }

        _members[m.get_visibility()].push_back(m);
}

void class_def::add_parent(const type_hint &t)
{
        _parents.push_back(t);
}

void class_def::add_design_pattern(const design_pattern &d)
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

vector<method> class_def::get_static_methods(const access_type *visibility) const
{
        return get_static<method>(_methods, visibility);
}

vector<member> class_def::get_members(const access_type *visibility) const
{
        return get<member>(_members, visibility);
}

vector<member> class_def::get_static_members(const access_type *visibility) const
{
        return get_static<member>(_members, visibility);
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

template<class T>
vector<T> class_def::get_static(const map<access_type,vector<T>> &m, const access_type *visibility) const {
        vector<T> v_tmp = get<T>(m, visibility);
        vector<T> s_tmp;
        for (T t : v_tmp) {
                class_component *cc = dynamic_cast<class_component*>(&t);
                if (cc != nullptr && cc->is_static()) {
                        s_tmp.push_back(t);
                }
        }
        return s_tmp;
        
}

