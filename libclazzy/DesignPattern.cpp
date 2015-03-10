
#include "DesignPattern.h"
#include <stdexcept>
using namespace clazzy;
using namespace std;

string clazzy::to_string(const DesignPattern& pattern) {
    switch (pattern) {
    case SINGLETON:
        return "singleton";
    case MULTITON:
        return "multiton";
    }
    return "";
}

DesignPattern clazzy::to_design_pattern(const string& str) {
    if (str == "singleton") {
        return SINGLETON;
    } else if (str == "multiton") {
        return MULTITON;
    }
    invalid_argument("No design pattern for value: " + str);
    // should never happen?
    return SINGLETON;
}

