
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

void class_def::add_parent(const string &name)
{
        parents.push_back(name);
}

vector<function> class_def::get_functions() const
{
        return functions;
}

vector<member> class_def::get_members() const
{
        return members;
}

vector<string> class_def::get_parents() const
{
        return parents;
}

