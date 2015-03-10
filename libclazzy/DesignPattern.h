#ifndef CLAZZY_DESIGN_PATTERN_H
#define CLAZZY_DESIGN_PATTERN_H

#include <string>

namespace clazzy {
    enum DesignPattern {
        SINGLETON,
        MULTITON
    };

    std::string   to_string(const DesignPattern&);
    DesignPattern to_design_pattern(const std::string&);
}

#endif // CLAZZY_DESIGN_PATTERN_H
