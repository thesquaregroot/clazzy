
#include "h/lang_python.h"
#include "h/class_def.h"
#include "h/function.h"
#include "h/member.h"
#include <vector>
#include <map>
#include <string>
#include <mutex>
using namespace cranberry;
using namespace std;

string lang_python::get_name() const
{
        return "Python";
}

void lang_python::create(
                        const vector<class_def> &classes,
                        const map<string,string> &properties
        ) const
{
        // TODO: Implement code generation
}
