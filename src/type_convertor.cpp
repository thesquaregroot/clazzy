
#include "type_convertor.h"
#include "string_functions.h"
#include <unordered_set>
using namespace clazzy;
using namespace std;

// char _generic_start
// char _generic_end
// case_conversion _default_case

// map<string,string> _mappings
// map<string,string> _imports

void type_convertor::add_type(const string &clazzy_type, const string &lang_type, const string * const import_stmt)
{
    _mappings[clazzy_type] = lang_type;
    if (import_stmt != nullptr) {
        _imports[clazzy_type] = *import_stmt;
    }
}

string type_convertor::convert_with_case(const type_hint &in_type, case_conversion cc) const
{
    string out_type;
    auto it = _mappings.find(in_type.get_base_type());
    if (it == _mappings.end()) {
        // could not find type, use given clazzy type
        switch (cc) {
        case LOWER:
            out_type = to_lower_case(in_type.get_base_type());
            break;
        case CAMEL:
            out_type = to_full_camel_case(in_type.get_base_type());
            break;
        case NONE:
            // default to NONE
            out_type = in_type.get_base_type();
            break;
        }
    } else {
        out_type = it->second;
    }
    if (_generic_start != '\0' && _generic_end != '\0') {
        // actually need to print generics
        vector<type_hint> generics = in_type.get_generic_types();
        if (generics.size() > 0) {
            out_type += _generic_start;
            for (unsigned int i=0; i<generics.size(); i++) {
                out_type += this->convert_with_case(generics[i], cc);
                if (i != generics.size()-1) {
                    out_type += ",";
                }
            }
            out_type += _generic_end;
        }
    }
    return out_type;
}

// convert with case as-is
string type_convertor::convert(const type_hint &in_type) const
{
    return convert_with_case(in_type, _default_case);
}

// convert to lower_case with underscores
string type_convertor::convert_lc(const type_hint &in_type) const
{
    return convert_with_case(in_type, LOWER);
}

// convert to camel case
string type_convertor::convert_cc(const type_hint &in_type) const
{
    return convert_with_case(in_type, CAMEL);
}

bool type_convertor::has_import(const string &name) const
{
    auto it = _imports.find(name);
    return it != _imports.end();
}

vector<string> type_convertor::get_imports(const vector<type_hint> &types) const
{
    unordered_set<string> imps;
    for (type_hint t : types) {
        if (has_import(t.get_base_type())) {
            imps.insert(_imports.find(t.get_base_type())->second);
        }
        for (string import : get_imports(t.get_generic_types())) {
            imps.insert(import);
        }
    }
    vector<string> vimps;
    for (string s : imps) {
        vimps.push_back(s);
    }
    return vimps;
}

