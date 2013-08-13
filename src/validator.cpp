
#include "h/validator.h"
using namespace clazzy;
using namespace std;

void validator::validate(class_def &clazz)
{
        // get types
        for (method m : clazz.get_methods()) {
                // return type
                add_type(m.get_return_type());
                // parameters
                for (auto param : m.get_parameters()) {
                        add_type(param.second);
                }
        }
        for (member m : clazz.get_members()) {
                add_type(m.get_type());
        }
        
        // validate types
        for (type_hint *t : _types_encountered) {
                // TODO: do validation
                if (t->get_base_type() == "map") {
                        if (t->get_generic_types().size() != 2) {
                                // ERROR
                        }
                }
        }
        
        // give class its types
        clazz.set_referenced_types(_types_encountered);
}

void validator::validate(vector<class_def> &clazzes)
{
        for (class_def &c : clazzes) {
                validate(c);
        }
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

