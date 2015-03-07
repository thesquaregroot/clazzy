#ifndef CLAZZY_STRING_HELPERS_H
#define CLAZZY_STRING_HELPERS_H

#include <string>

namespace clazzy {
    std::string to_lower_case(const std::string&);
    std::string to_camel_case(const std::string&);
    std::string to_full_camel_case(const std::string&);
}

#endif // CLAZZY_STRING_HELPERS_H
