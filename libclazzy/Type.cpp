
#include "Type.h"
using namespace clazzy;
using std::string;
using std::vector;

vector<string> parse_generics(const string&);

string clazzy::to_string(const BaseType& type) {
    switch (type) {
    // generic types
    case BaseType::ARRAY:
        return "array";
    case BaseType::DEQUE:
        return "deque";
    case BaseType::LIST:
        return "list";
    case BaseType::MAP:
        return "map";
    case BaseType::QUEUE:
        return "queue";
    case BaseType::SET:
        return "set";
    case BaseType::STACK:
        return "stack";
    // primitive types
    case BaseType::BOOLEAN:
        return "boolean";
    case BaseType::BYTE:
        return "byte";
    case BaseType::CHARACTER:
        return "character";
    case BaseType::DOUBLE:
        return "double";
    case BaseType::FLOAT:
        return "float";
    case BaseType::INTEGER:
        return "integer";
    case BaseType::LONG:
        return "long";
    case BaseType::SHORT:
        return "short";
    case BaseType::STRING:
        return "string";
    case BaseType::VOID:
        return "void";
    case BaseType::USER_DEFINED:
    default:
        // don't know the user defined type
        return "";
    }
}

BaseType clazzy::to_base_type(const string& str) {
    if (str.length() == 0) {
        return BaseType::USER_DEFINED;
    }
    switch (str[0]) {
    case 'a': {
        if (str == "array") {
            return BaseType::ARRAY;
        }
    } break;
    case 'b': {
        if (str == "boolean") {
            return BaseType::BOOLEAN;
        }
        if (str == "byte") {
            return BaseType::BYTE;
        }
    } break;
    case 'c': {
        if (str == "character") {
            return BaseType::CHARACTER;
        }
    } break;
    case 'd': {
        if (str == "deque") {
            return BaseType::DEQUE;
        }
        if (str == "double") {
            return BaseType::DOUBLE;
        }
    } break;
    case 'f': {
        if (str == "float") {
            return BaseType::FLOAT;
        }
    } break;
    case 'i': {
        if (str == "integer") {
            return BaseType::INTEGER;
        }
    } break;
    case 'l': {
        if (str == "list") {
            return BaseType::LIST;
        }
    } break;
    case 'm': {
        if (str == "map") {
            return BaseType::MAP;
        }
    } break;
    case 'q': {
        if (str == "queue") {
            return BaseType::QUEUE;
        }
    } break;
    case 's': {
        if (str == "set") {
            return BaseType::SET;
        }
        if (str == "short") {
            return BaseType::SHORT;
        }
        if (str == "stack") {
            return BaseType::STACK;
        }
        if (str == "string") {
            return BaseType::STRING;
        }
    } break;
    case 'v': {
        if (str == "void") {
            return BaseType::VOID;
        }
    } break;
    }
    // not sure, must be user defined
    return BaseType::USER_DEFINED;
}

Type::Type() {
    _base_type = BaseType::USER_DEFINED;
    _user_type_name = "";
}

Type::Type(const BaseType& type, const std::string& user_type_name) {
    _base_type = type;
    _user_type_name = user_type_name;
}

// converts "<type_1, type_2, type_3>" into a vector
//  containing ["type_1", "type_2", "type_3"]
//  not that each type could be generic (i.e., contain '<>')
vector<string> parse_generics(const string& str) {
    vector<string> generics;
    string raw_list = str.substr(1, str.length()-2);
    // read until comma or end, ensuring we're not within a sub-generic type
    size_t current_start = 0;
    int bracket_depth = 0;
    for (size_t i=0; i<raw_list.length(); i++) {
        if (raw_list[i] == '<') {
            bracket_depth++;
        }
        if (raw_list[i] == '>') {
            bracket_depth--;
        }
        if (raw_list[i] == ',' && bracket_depth == 0) {
            generics.push_back(raw_list.substr(current_start, i-1-current_start));
        } else if (i == raw_list.length()-1) {
            generics.push_back(raw_list.substr(current_start));
            break;
        }
    }
    return generics;
}

Type::Type(const string& type_string) {
    size_t lt_pos = type_string.find('<');
    bool generic = lt_pos != string::npos;

    string base_type = generic ? type_string.substr(0, lt_pos) : type_string;
    _base_type = to_base_type(base_type);

    if (generic) {
        if (type_string[type_string.length()-1] == '>') {
            // looks like: base_type<..generics..>
            // get generic types and parse
            vector<string> generics = parse_generics(type_string.substr(lt_pos));
            for (string str : generics) {
                _generic_types.push_back(Type(str));
            }
        }
    }
}

BaseType Type::get_base_type() const {
    return _base_type;
}

void Type::set_base_type(const BaseType& type) {
    _base_type = type;
}

std::string Type::get_user_type_name() const {
    return _user_type_name;
}

void Type::set_user_type_name(const std::string& name) {
    _user_type_name = name;
}

std::vector<Type> Type::get_generic_types() const {
    return _generic_types;
}

void Type::add_generic_type(const Type& type) {
    _generic_types.push_back(type);
}

string Type::to_string() const {
    string str = clazzy::to_string(_base_type);
    if (_generic_types.size() > 0) {
        str += "<";
        for (unsigned int i=0; i<_generic_types.size(); i++) {
                str += _generic_types[i].to_string();
                if (i != _generic_types.size()-1) {
                        str += ",";
                }
        }
        str += ">";
    }
    return str;
}

bool Type::operator==(const Type& type) {
    // check for different base type
    if (this->_base_type != type._base_type) {
        return false;
    }
    // check for different generic types
    if (this->_generic_types.size() != type._generic_types.size()) {
        // wrong number of generic arguments
        return false;
    } else {
        // correct number of generic arguments
        for (size_t i=0; i<this->_generic_types.size(); i++) {
            if (this->_generic_types[i] != type._generic_types[i]) {
                return false;
            }
        }
        // everything matches
        return true;
    }
}

bool Type::operator!=(const Type& type) {
    return !(*this == type);
}

