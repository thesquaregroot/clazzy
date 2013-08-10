
#include "h/type_convertor.h"
using namespace clazzy;
using namespace std;

// map<string,string> mappings

void type_convertor::add_type(const string &cran_type, const string &lang_type)
{
        mappings[cran_type] = lang_type;
}

string type_convertor::convert(const type_hint &in_type, char generic_start, char generic_end) const
{
        string out_type;
        auto it = mappings.find(in_type.get_base_type());
        if (it == mappings.end()) {
                out_type = in_type.get_base_type();
        } else {
                out_type = it->second;
        }
        vector<type_hint> generics = in_type.get_generic_types();
        if (generics.size() > 0) {
                out_type += generic_start;
                for (int unsigned i=0; i<generics.size(); i++) {
                        out_type += this->convert(generics[i], generic_start, generic_end);
                        if (i != generics.size()-1) {
                                out_type += ",";
                        }
                }
                out_type += generic_end;
        }
        return out_type;
}

