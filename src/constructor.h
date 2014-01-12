#ifndef __CONSTRUCTOR_H__
#define __CONSTRUCTOR_H__

#include "parameterized.h"
#include "accessible.h"

namespace clazzy {
    class constructor : public parameterized, public accessible {};
}

#endif
