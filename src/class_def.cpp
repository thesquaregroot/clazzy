
#include "h/class_def.h"
#include "h/method.h"
#include "h/member.h"
#include <string>
#include <vector>
using namespace cranberry;
using namespace std;

// string name
// vector<method> methods
// vector<member> members
// vector<type_hint> parents

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

void class_def::add_method(method &m)
{
        _methods.push_back(m);
}

void class_def::add_member(member &m)
{
        _members.push_back(m);
}

void class_def::add_parent(type_hint &t)
{
        _parents.push_back(t);
}

vector<method> class_def::get_methods() const
{
        return _methods;
}

vector<member> class_def::get_members() const
{
        return _members;
}

vector<type_hint> class_def::get_parents() const
{
        return _parents;
}

