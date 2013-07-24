
#include "h/lang_cpp.h"
#include "h/class_def.h"
#include "h/method.h"
#include "h/member.h"
#include <vector>
#include <map>
#include <string>
#include <mutex>
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
        for (class_def c : classes) {
                debug("Creating code for class: " + c.get_name());
        }
}
