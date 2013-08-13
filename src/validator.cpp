
#include "h/validator.h"
using namespace clazzy;
using namespace std;

void validator::validate(class_def &clazz)
{
        for (method m : clazz.get_methods()) {
                // return
                add_type(m.get_return_type());
                // parameters
                // TODO
        }
        for (member m : clazz.get_members()) {
                add_type(m.get_type());
        }
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
        types_encountered.push_back(t);
}

// returns added types and clears the current state
vector<type_hint> validator::get_types()
{
        vector<type_hint> tmp = types_encountered;
        types_encountered.clear();
        return tmp;
}

