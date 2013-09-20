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

        private:
            std::map<std::string, type_hint> _params;
    };
}

#endif
