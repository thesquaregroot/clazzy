#ifndef __CLAZZY_MEMBER_H__
#define __CLAZZY_MEMBER_H__

#include "declarable.h"
#include "type_hint.h"
#include <string>

namespace clazzy {
    class member : public declarable {
        public:
            member(const type_hint &, const std::string &);

            std::string get_name() const;
            type_hint get_type() const;

            bool is_static() const;
            void set_static(const bool &);
            bool is_constant() const;
            void set_constant(const bool &);

            bool has_getter() const;
            void set_getter(const bool);
            bool has_setter() const;
            void set_setter(const bool);
            bool has_get_set() const;        // True IFF both get && set
            void set_get_set(const bool);   // Sets both get && set

        private:
            std::string _name;
            type_hint _type;
            bool _is_static = false;
            bool _is_constant = false;

            short _getter_setter = 0;   // automatically print getter and setters
                                        // 0: neither, 1: getter, 2: setter, 3: both
    };
}

#endif
