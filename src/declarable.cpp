
#include "h/declarable.h"
using namespace clazzy;
using namespace std;

// access_type _visibility

access_type declarable::get_visibility() const
{
        return _visibility;
}

void declarable::set_visibility(const access_type &val)
{
        _visibility = val;
}

