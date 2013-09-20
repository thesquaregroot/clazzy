#ifndef __CALLABLE_H__
#define __CALLABLE_H__

#include "type_hint.h"
#include "access_type.h"
#include <map>
#include <string>

namespace clazzy {
    class callable {
        public:
            void add_parameter(type_hint, std::string);
            std::map<std::string, type_hint> get_parameters() const;

            access_type get_visibility() const;
            void set_visibility(const access_type &);

        private:
            std::map<std::string, type_hint> _params;
            access_type _visibility = VISIBLE_ACCESS; // think public, private, etc.
    };
}

#endif
