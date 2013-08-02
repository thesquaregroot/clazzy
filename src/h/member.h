#ifndef __CRANBERRY_MEMBER_H__
#define __CRANBERRY_MEMBER_H__

#include "type_hint.h"
#include <string>

namespace cranberry {
    class member {
        public:
            member(const type_hint &, const std::string &);

            std::string get_name() const;
            type_hint get_type() const;

            bool is_static() const;
            void set_static(const bool &);
            bool is_constant() const;
            void set_constant(const bool &);

        private:
            std::string _name;
            type_hint _type;
            bool _is_static = false;
            bool _is_constant = false;
    };
}

#endif
