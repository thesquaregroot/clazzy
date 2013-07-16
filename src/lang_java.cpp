
#include "h/lang_java.h"
#include <vector>
#include <map>
#include <string>
using namespace cranberry;
using namespace std;

string lang_java::get_name() const
{
        return "Java";
}

void lang_java::create(
                        const vector<class_def> &classes,
                        const map<string,string> &properties
        ) const
{
        // TODO
}
