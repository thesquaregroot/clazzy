#ifndef __CLASS_COMPONENT_H__
#define __CLASS_COMPONENT_H__

#include "accessible.h"

namespace clazzy {
    class class_component : public accessible {
        public:
            bool is_static() const;
            void set_static(const bool);

            bool is_read_only() const;
            void set_read_only(const bool);

        private:
            bool _is_static = false;
            bool _is_read_only = false;
    };
}

#endif
