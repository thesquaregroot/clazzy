#ifndef __CLAZZY_STRING_FUNCTIONS_H__
#define __CLAZZY_STRING_FUNCTIONS_H__

#include <string>

namespace clazzy {
    std::string to_lower_case(const std::string &text);
    std::string to_camel_case(const std::string &text);
    std::string to_full_camel_case(const std::string &text);
}

#endif
