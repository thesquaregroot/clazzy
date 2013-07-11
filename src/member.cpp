
#include "h/member.h"
#include <string>
using namespace cranberry;
using namespace std;

member::member(const string& name)
{
        this->name = name;
}

string member::get_name() const
{
        return name;
}

