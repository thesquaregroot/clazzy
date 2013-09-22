#ifndef __CONSTRUCTOR_H__
#define __CONSTRUCTOR_H__

#include "callable.h"
#include "declarable.h"

namespace clazzy {
    class constructor : public callable, public declarable {};
}

#endif
