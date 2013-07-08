
#include "h/class_def.h"
#include <map>
#include <string>
#include <vector>
using namespace std;

// string name
// map<string, vector<string> > functions
// vector<string> memebers

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


void class_def::add_function(const string &name, vector<string> &params)
{
        functions[name] = params;
}

void class_def::add_member(const string &name)
{
        members.push_back(name);
}

void class_def::add_parent(const string &name)
{
        parents.push_back(name);
}

map<string, vector<string> > class_def::get_functions() const
{
        return functions;
}

vector<string> class_def::get_members() const
{
        return members;
}

vector<string> class_def::get_parents() const
{
        return parents;
}

