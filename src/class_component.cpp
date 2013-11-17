
#include "h/class_component.h"
using namespace clazzy;
using namespace std;

// bool _is_static
// bool _is_read_only

bool class_component::is_static() const
{
        return _is_static;
}

void class_component::set_static(const bool val)
{
        _is_static = val;
}

bool class_component::is_read_only() const
{
        return _is_read_only;
}

void class_component::set_read_only(const bool val)
{
        _is_read_only = val;
}

