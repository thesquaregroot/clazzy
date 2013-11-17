#ifndef __ACCESSIBLE_H__
#define __ACCESSIBLE_H__

#include "access_type.h"

namespace clazzy {
    class accessible {
        public:
            void set_visibility(const access_type);
            access_type get_visibility() const;
            
        private:
            access_type _visibility = VISIBLE_ACCESS; // think public, private, etc.
    };
}
#endif
