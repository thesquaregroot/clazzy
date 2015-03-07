
#include "Type.h"
using namespace clazzy;
using std::string;
using std::vector;

Type::Type() {
    _base_type = BaseType::USER_DEFINED;
    _user_type_name = "";
}

Type::Type(const BaseType& type) {
    _base_type = type;
}

Type::Type(const string& name) {
    _base_type = BaseType::USER_DEFINED;
    _user_type_name = name;
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

