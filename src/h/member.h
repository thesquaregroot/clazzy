#ifndef __CLAZZY_MEMBER_H__
#define __CLAZZY_MEMBER_H__

#include "declarable.h"
#include "type_hint.h"
#include <string>

namespace clazzy {
    class member : public declarable {
        public:
            member(const type_hint &, const std::string &);
            member(const member&) = default;

            std::string get_name() const;
            type_hint get_type() const;

            bool is_static() const;
            void set_static(const bool);
            bool is_constant() const;
            void set_constant(const bool);

            bool has_getter() const;
            std::string get_getter_name() const;
            void set_getter(const bool, const std::string& = "");
            bool has_setter() const;
            std::string get_setter_name() const;
            void set_setter(const bool, const std::string& = "");
            bool has_get_set() const;        // True IFF both get && set
            void set_get_set(const bool, const std::string& = "", const std::string& = "");   // Sets both get && set

            bool is_initialized() const;
            void set_initialized(const bool);

        private:
            std::string _name;
            type_hint _type;
            bool _is_static = false;
            bool _is_constant = false;

            // automatically print getter and setters
            // 0: neither, 1: getter, 2: setter, 3: both
            short _getter_setter = 0;
            static const short _NEITHER = 0x00;
            static const short _GETTER  = 0x01;
            static const short _SETTER  = 0x02;
            static const short _BOTH    = 0x03;
            std::string _getter_name;
            std::string _setter_name;

            bool _is_initialized = false;
    };
}

#endif
