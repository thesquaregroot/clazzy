#ifndef __CLAZZY_TYPE_CONVERTOR__
#define __CLAZZY_TYPE_CONVERTOR__

#include "type_hint.h"
#include <string>
#include <map>

namespace clazzy {
    class type_convertor {
        public:
            void add_type(const std::string &clazzy_type, const std::string &lang_type, const std::string * const import_stmt = nullptr);
            // converts with case as-is
            std::string convert(const type_hint &, char generic_start = '<', char generic_end = '>') const;
            // converts all type names to lower-case with underscores (like_this)
            std::string convert_lc(const type_hint &, char generic_start = '<', char generic_end = '>') const;
            // converts all type names to camel case (LikeThis)
            std::string convert_cc(const type_hint &, char generic_start = '<', char generic_end = '>') const;

            bool has_import(const std::string &) const;
            std::vector<std::string> get_imports(const std::vector<type_hint> &) const;

        private:
            enum case_conversion {
                NONE,
                LOWER,
                CAMEL
            };

            std::string convert_with_case(const type_hint &, char generic_start = '<', char generic_end = '>', case_conversion = NONE) const;

            std::map<std::string,std::string> mappings;
            std::map<std::string,std::string> imports;
    };
}

#endif
