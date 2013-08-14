
#include "h/validator.h"
using namespace clazzy;
using namespace std;

string validator::validate(class_def &clazz)
{
        string error;

        // get types
        for (method m : clazz.get_methods()) {
                // return type
                error += validate(m.get_return_type());
                // parameters
                for (auto param : m.get_parameters()) {
                        error += validate(param.second);
                }
        }
        for (member m : clazz.get_members()) {
                error += validate(m.get_type());
        }
        
        // give class its types
        clazz.set_referenced_types(_types_encountered);
        
        if (error != "") {
                error = "In definition of class '" + clazz.get_name() + "':\n" + error;
        }
        return error;
}

string validator::validate(vector<class_def> &clazzes)
{
        string errors;
        for (class_def &c : clazzes) {
                errors += validate(c);
        }
        return errors;
}

string validator::validate(const type_hint &t)
{
        string type = t.get_base_type();
        int size = t.get_generic_types().size();
        
        string error;
        if (type == "array") {
                if (size != 1) {
                        error = "Type 'array' must have only 1 parameter.\n";
                }
        } else if (type == "deque") {
                if (size != 1) {
                        error = "Type 'deque' must have only 1 parameter.\n";
                }
        } else if (type == "list") {
                if (size != 1) {
                        error = "Type 'list' must have only 1 parameter.\n";
                }
        } else if (type == "set") {
                if (size != 1) {
                        error = "Type 'set' must have only 1 parameter.\n";
                }
        } else if (type == "stack") {
                if (size != 1) {
                        error = "Type 'stack' must have only 1 parameter.\n";
                }
        } else if (type == "queue") {
                if (size != 1) {
                        error = "Type 'queue' must have only 1 parameter.\n";
                }
        } else if (type == "map") {
                if (size != 2) {
                        error = "Type 'map' must have exactly 2 parameters.\n";
                }
        } else if (type == "pointer") {
                if (size != 1) {
                        error = "Type 'pointer' must have only 1 parameter.\n";
                }
        } else {
                add_type(t);
        }
        return error;
}

// remembers a type temporarily
void validator::add_type(const type_hint &t)
{
        _types_encountered.push_back((type_hint*) &t);
}

// returns added types and clears the current state
vector<type_hint*> validator::get_types()
{
        vector<type_hint*> tmp = _types_encountered;
        _types_encountered.clear();
        return tmp;
}

