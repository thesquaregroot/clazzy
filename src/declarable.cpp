
#include "h/declarable.h"
using namespace clazzy;
using namespace std;

// access_type _visibility
// bool _is_static

access_type declarable::get_visibility() const
{
        return _visibility;
}

void declarable::set_visibility(const access_type &val)
{
        _visibility = val;
}

bool declarable::is_static() const
{
        return _is_static;
}

void declarable::set_static(const bool val)
{
        _is_static = val;
}

