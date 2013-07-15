
#include "h/lang_cpp.h"
#include <vector>
#include <map>
#include <string>
using namespace cranberry;
using namespace std;

string lang_cpp::get_name() const
{
        return "C++";
}

void lang_cpp::create(
                        const vector<class_def> &classes,
                        const map<string,string> &properties
        ) const
{
        // TODO
}
