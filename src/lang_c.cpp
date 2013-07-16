
#include "h/lang_c.h"
#include <vector>
#include <map>
#include <string>
#include <mutex>
using namespace cranberry;
using namespace std;

// mutex io_mutex

string lang_c::get_name() const
{
        return "C";
}

void lang_c::create(
                        const vector<class_def> &classes,
                        const map<string,string> &properties
        ) const
{
        // TODO
}
