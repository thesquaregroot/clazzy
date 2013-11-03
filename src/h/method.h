#ifndef __CLAZZY_METHOD_H__
#define __CLAZZY_METHOD_H__

#include "declarable.h"
#include "callable.h"
#include "member.h"
#include <map>
#include <string>

namespace clazzy {
    class method : public declarable, public callable {
        public:
            method(type_hint, std::string);
            method(const method &);
            ~method();
            
            std::string get_name() const;
            type_hint get_return_type() const;

            bool is_read_only() const;
            void set_read_only(const bool &);

            bool is_getter() const;
            void set_getter(bool, const member* const = nullptr); // member is optional if setting to false. member* can be a dynamic variable; we don't store its address: it is copied.
            bool is_setter() const;
            void set_setter(bool, const member* const = nullptr); // member is optional if setting to false. member* can be a dynamic variable; we don't store its address: it is copied.
            const member* get_getter_member() const;
            const member* get_setter_member() const;

        private:
            std::string _name;
            type_hint _return_type;
            bool _is_read_only = false; // think const keyword in C++

            member* _getter_member = nullptr;
            member* _setter_member = nullptr;
    };
}

#endif
