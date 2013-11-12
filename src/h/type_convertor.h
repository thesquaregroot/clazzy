#ifndef __CLAZZY_TYPE_CONVERTOR__
#define __CLAZZY_TYPE_CONVERTOR__

#include "type_hint.h"
#include <string>
#include <map>

namespace clazzy {
    class type_convertor {
        public:
            enum case_conversion {
                NONE,
                LOWER,
                CAMEL
            };

            type_convertor() = default;
            type_convertor(char gstart, char gend, case_conversion cc = NONE) : _generic_start(gstart),
                                                                        _generic_end(gend),
                                                                        _default_case(cc) {};

            void add_type(const std::string &clazzy_type, const std::string &lang_type, const std::string * const import_stmt = nullptr);
            // converts with case as-is
            std::string convert(const type_hint &) const;
            // converts all type names to lower-case with underscores (like_this)
            std::string convert_lc(const type_hint &) const;
            // converts all type names to camel case (LikeThis)
            std::string convert_cc(const type_hint &) const;

            bool has_import(const std::string &) const;
            std::vector<std::string> get_imports(const std::vector<type_hint> &) const;

        private:
            char _generic_start = '<';
            char _generic_end = '>';
            case_conversion _default_case = NONE;
            
            std::map<std::string,std::string> _mappings;
            std::map<std::string,std::string> _imports;
            
            std::string convert_with_case(const type_hint &, const case_conversion) const;
    };
}

#endif
