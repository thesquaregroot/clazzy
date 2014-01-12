#ifndef __CLAZZY_DESIGN_PATTERN__
#define __CLAZZY_DESIGN_PATTERN__

#include <map>
#include <string>

namespace clazzy {
    enum design_pattern {
        SINGLETON
        //MULTITON
    };

    static std::map<std::string, design_pattern> design_pattern_map;
}

#endif
