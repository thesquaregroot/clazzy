
#include "h/class_def.h"
#include <string>
#include <vector>
using namespace clazzy;
using namespace std;

// string _name
// map<access_type,vector<constructor> _ctors;
// map<access_type,vector<method>> _methods
// map<access_type,vector<member>> _members
// vector<type_hint> _parents
// vector<type_hint _referenced_types
// vector<design_pattern> _design_pattern

class_def::class_def(const string& name)
{
        _name = name;
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

vector<constructor> class_def::get_constructors(const access_type *visibility, short types) const
{
        if (visibility != nullptr) {
                // return constructors with given visibilty
                auto it = _ctors.find(*visibility);
                if (it != _ctors.end()) {
                        if (types == ALL_CTORS) {
                                return it->second;
                        } else {
                                vector<constructor> selected;
                                for (constructor c : it->second) {
                                        if (c.is_destructor() && types | DTORS) {
                                                // destructor and we want destructors
                                                selected.push_back(c);
                                        }
                                        if ((!c.is_destructor()) && types | CTORS) {
                                                // not destructor (so actually a constructor)
                                                // and we're looking for constructors
                                                selected.push_back(c);
                                        }
                                }
                        }
                }
                return vector<constructor>();
        }
        // return all constructors
        vector<constructor> all_constructors;
        for (auto p : _ctors) {
                for (constructor m : p.second) {
                        all_constructors.push_back(m);
                }
        }
        return all_constructors;
}

vector<method> class_def::get_methods(const access_type *visibility) const
{
        if (visibility != nullptr) {
                // return methods with given visibilty
                auto it = _methods.find(*visibility);
                if (it != _methods.end()) {
                        return it->second;
                }
                return vector<method>();
        }
        // return all methods
        vector<method> all_methods;
        for (auto p : _methods) {
                for (method m : p.second) {
                        all_methods.push_back(m);
                }
        }
        return all_methods;
}

vector<member> class_def::get_members(const access_type *visibility) const
{
        if (visibility != 0) {
                // return members with given visibilty
                auto it = _members.find(*visibility);
                if (it != _members.end()) {
                        return it->second;
                }
                return vector<member>();
        }
        // return all members
        vector<member> all_members;
        for (auto p : _members) {
                for (member m : p.second) {
                        all_members.push_back(m);
                }
        }
        return all_members;
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

