#ifndef MEMBER_H
#define MEMBER_H

#include "type_hint.h"
#include <string>

namespace cranberry {
    class member {
        public:
            member(const type_hint &, const std::string &);

            std::string get_name() const;
            type_hint get_type() const;

            bool is_constant() const;
            void set_constant(const bool &);
            bool is_reference() const;
            void set_reference(const bool &);

        private:
            std::string _name;
            type_hint _type;
            bool _is_constant = false;
            bool _is_reference = false;
    };
}

#endif
