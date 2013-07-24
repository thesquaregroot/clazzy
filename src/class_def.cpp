
#include "h/class_def.h"
#include "h/function.h"
#include "h/member.h"
#include <string>
#include <vector>
using namespace cranberry;
using namespace std;

// string name
// vector<function> functions
// vector<member> members
// vector<type_hint> parents

class_def::class_def(const string& name)
{
        this->name = name;
}


void class_def::set_name(const string& name)
{
        this->name = name;
}

string class_def::get_name() const
{
        return name;
}

void class_def::add_function(function &f)
{
        functions.push_back(f);
}

void class_def::add_member(member &m)
{
        members.push_back(m);
}

void class_def::add_parent(type_hint &t)
{
        parents.push_back(t);
}

vector<function> class_def::get_functions() const
{
        return functions;
}

vector<member> class_def::get_members() const
{
        return members;
}

vector<type_hint> class_def::get_parents() const
{
        return parents;
}

