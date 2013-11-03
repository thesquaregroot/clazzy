#ifndef __DECLARABLE_H__
#define __DECLARABLE_H__

#include "access_type.h"

namespace clazzy {
    class declarable {
        public:
            access_type get_visibility() const;
            void set_visibility(const access_type &);
            
            bool is_static() const;
            void set_static(const bool);

        private:
            access_type _visibility = VISIBLE_ACCESS; // think public, private, etc.
            bool _is_static = false;
    };
}

#endif
