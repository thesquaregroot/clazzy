
#include "h/type_hint.h"
using namespace clazzy;
using namespace std;

// type _base_type
// vector<type> _generic_types

type_hint::type_hint(string base, const std::vector<type_hint> &generics)
{
        _base_type = base;
        _generic_types = generics;
}


string type_hint::get_base_type() const
{
        return _base_type;
}

vector<type_hint> type_hint::get_generic_types() const
{
        return _generic_types;
}

string type_hint::to_string() const
{
        string s = _base_type;
        if (_generic_types.size() > 0) {
                s += "<";
                for (unsigned int i=0; i<_generic_types.size(); i++) {
                        s += _generic_types[i].to_string();
                        if (i != _generic_types.size()-1) {
                                s += ",";
                        }
                }
                s += ">";
        }
        return s;
}

bool type_hint::operator==(const type_hint &t) const
{
        if (_base_type != t._base_type || _generic_types.size() != t._generic_types.size()) {
                return false;
        }
        // same base, same number of generics, check the generics
        for (unsigned int i=0; i<_generic_types.size(); i++) {
                if (_generic_types[i] != t._generic_types[i]) {
                        return false;
                }
        }
        // same base, same generics (must be the same)
        return true;
}

bool type_hint::operator!=(const type_hint &t) const
{
        return !(*this == t);
}

