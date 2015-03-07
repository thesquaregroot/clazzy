#ifndef CLAZZY_ARGUMENT_H
#define CLAZZY_ARGUMENT_H

#include <string>
#include "Type.h"

namespace clazzy {
    class Argument {
    public:
        Argument(const std::string& name);

        std::string get_name() const;
        void        set_name(const std::string&);

        Type get_type() const;
        void set_type(const Type&);

        bool is_read_only() const;
        void set_read_only(bool);

        std::string get_default_value() const;
        void        set_default_value(const std::string&);

    private:
        std::string _name;
        Type        _type;
        bool        _is_read_only;
        std::string _default_value;
    };
}

#endif // CLAZZY_ARGUMENT_H
