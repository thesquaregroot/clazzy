#ifndef __CLAZZY_METHOD_H__
#define __CLAZZY_METHOD_H__

#include "class_component.h"
#include "parameterized.h"
#include "member.h"
#include <map>
#include <string>

namespace clazzy {
    class method : public class_component, public parameterized {
        public:
            method(type_hint, std::string);
            method(const method &);
            ~method();
            
            std::string get_name() const;
            type_hint get_return_type() const;

            bool is_getter() const;
            void set_getter(const member* const); // member* can be a dynamic variable; we don't store its address: it is copied.
            bool is_setter() const;
            void set_setter(const member* const); // member* can be a dynamic variable; we don't store its address: it is copied.
            const member* get_member() const;

        private:
            std::string _name;
            type_hint _return_type;

            // member underlying getter/setter (iff _member != nullptr, _is_getter matters)
            member* _member = nullptr;
            bool _is_getter = false;

            // underlies set_getter and set_setter (the bool matches _is_getter in meaning)
            void set_member(const bool, const member* const);
    };
}

#endif
