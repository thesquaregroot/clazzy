#ifndef CLAZZY_TYPE_H
#define CLAZZY_TYPE_H

#include <string>
#include <vector>

namespace clazzy {
    enum BaseType {
        // Generic Types
        ARRAY,
        DEQUE,
        LIST,
        MAP,
        QUEUE,
        SET,
        STACK,
        USER_DEFINED,
        // Primitive Types
        BOOLEAN,
        BYTE,
        CHARACTER,
        DOUBLE,
        FLOAT,
        INTEGER,
        LONG,
        SHORT,
        STRING,
        VOID
    };

    class Type {
    public:
        // creates a default user type without a name
        Type();
        // creates a new type with the given base
        Type(const BaseType& type);
        // creates a new type for a user defined type denoted by "name".
        Type(const std::string& name);

        BaseType get_base_type() const;
        void     set_base_type(const BaseType&);

        std::string get_user_type_name() const;
        void        set_user_type_name(const std::string&);

        std::vector<Type> get_generic_types() const;
        void              add_generic_type(const Type&);

        bool operator==(const Type&);
        bool operator!=(const Type&);

    private:
        BaseType            _base_type;
        std::string         _user_type_name;
        std::vector<Type>   _generic_types;
    };
}

#endif // CLAZZY_TYPE_H
