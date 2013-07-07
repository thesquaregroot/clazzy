
#include "h/class_def.h"
#include <map>
#include <string>
#include <vector>
using namespace std;

// map<string, vector<string> > functions
// vector<string> memebers

void class_def::add_function(const string &name, vector<string> &params)
{
    functions[name] = params;
}

void class_def::add_member(const string &name)
{
    members.push_back(name);
}

map<string, vector<string> > class_def::get_functions() const
{
    return functions;
}

vector<string> class_def::get_members() const
{
    return members;
}

