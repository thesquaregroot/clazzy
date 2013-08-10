#ifndef __CLAZZY_TYPE_CONVERTOR__
#define __CLAZZY_TYPE_CONVERTOR__

#include "type_hint.h"
#include <string>
#include <map>

namespace clazzy {
    class type_convertor {
        public:
            void add_type(const std::string &cran_type, const std::string &lang_type);
            std::string convert(const type_hint &, char generic_start = '<', char generic_end = '>') const;

        private:
            std::map<std::string,std::string> mappings;
    };
}

#endif
