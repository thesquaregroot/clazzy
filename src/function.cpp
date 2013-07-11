
#include "h/function.h"
#include <vector>
#include <string>
using namespace cranberry;
using namespace std;

// string name
// vector<string> params

function::function(const string &name)
{
        this->name = name;
}

string function::get_name() const
{
        return name;
}

void function::add_parameter(const string &p)
{
        params.push_back(p);
}

vector<string> function::get_parameters() const
{
        return params;
}
