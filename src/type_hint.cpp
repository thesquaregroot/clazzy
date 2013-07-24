
#include "h/type_hint.h"
using namespace cranberry;
using namespace std;

// type base_type
// vector<type> generice_types

type_hint::type_hint(string base, std::vector<type_hint> &generics)
{
        base_type = base;
        generic_types = generics;
        is_primitive = (generics.size() == 0);
}


string type_hint::get_base_type() const
{
        return base_type;
}

vector<type_hint> type_hint::get_generic_types() const
{
        return generic_types;
}

string type_hint::to_string() const
{
        string s = base_type;
        if (generic_types.size() > 0) {
                s += "<";
                for (unsigned int i=0; i<generic_types.size(); i++) {
                        s += generic_types[i].to_string();
                        if (i != generic_types.size()-1) {
                                s += ",";
                        }
                }
                s += ">";
        }
        return s;
}

