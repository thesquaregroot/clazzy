#include "accessible.h"
using namespace clazzy;
using namespace std;

// access_type _visibility

void accessible::set_visibility(const access_type visibility)
{
    _visibility = visibility;
}

access_type accessible::get_visibility() const
{
    return _visibility;
}

