
#include "h/member.h"
#include <string>
using namespace cranberry;
using namespace std;

// string name
// type_hint type


member::member(const type_hint &type, const string& name)
{
        this->type = type;
        this->name = name;
}

string member::get_name() const
{
        return name;
}

type_hint member::get_type() const
{
        return type;
}

