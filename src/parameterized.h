#ifndef __PARAMETERS_H__
#define __PARAMETERS_H__

#include "type_hint.h"
#include "access_type.h"
#include <map>
#include <string>

namespace clazzy {
    class parameterized {
        public:
            void add_parameter(const type_hint&, const std::string&);
            std::map<std::string, type_hint> get_parameters() const;

        private:
            std::map<std::string, type_hint> _params;
    };
}

#endif
