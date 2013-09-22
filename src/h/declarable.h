#ifndef __DECLARABLE_H__
#define __DECLARABLE_H__

#include "access_type.h"

namespace clazzy {
    class declarable {
        public:
            access_type get_visibility() const;
            void set_visibility(const access_type &);

        private:
            access_type _visibility = VISIBLE_ACCESS; // think public, private, etc.
    };
}

#endif
