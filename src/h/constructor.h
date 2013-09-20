#ifndef __CONSTRUCTOR_H__
#define __CONSTRUCTOR_H__

#include "callable.h"
#include "declarable.h"

namespace clazzy {
    class constructor : public callable, public declarable {
        public:
            constructor(bool /* is_destructor */ = true);
            
            bool is_destructor() const;

        private:
            bool _is_destructor;
    };
}

#endif
