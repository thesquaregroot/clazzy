
#include "h/constructor.h"
using namespace clazzy;
using namespace std;

// bool _is_destructor

constructor::constructor(bool is_destructor)
{
        _is_destructor = is_destructor;
}

bool constructor::is_destructor() const
{
        return _is_destructor;
}

