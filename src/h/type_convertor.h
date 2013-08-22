#ifndef __CLAZZY_TYPE_CONVERTOR__
#define __CLAZZY_TYPE_CONVERTOR__

#include "type_hint.h"
#include <string>
#include <map>

namespace clazzy {
    class type_convertor {
        public:
            void add_type(const std::string &clazzy_type, const std::string &lang_type, const std::string * const import_stmt = nullptr);
            std::string convert(const type_hint &, char generic_start = '<', char generic_end = '>') const;

            bool has_import(const std::string &) const;
            std::vector<std::string> get_imports(const std::vector<type_hint> &) const;

        private:
            std::map<std::string,std::string> mappings;
            std::map<std::string,std::string> imports;
    };
}

#endif
