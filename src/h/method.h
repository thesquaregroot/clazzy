#ifndef __CLAZZY_METHOD_H__
#define __CLAZZY_METHOD_H__

#include "type_hint.h"
#include "access_type.h"
#include "member.h"
#include <map>
#include <string>

namespace clazzy {
    class method {
        public:
            method(type_hint, std::string);
            method(const method &);
            ~method();
            
            std::string get_name() const;
            type_hint get_return_type() const;
            void add_parameter(type_hint, std::string);
            std::map<std::string, type_hint> get_parameters() const;

            bool is_static() const;
            void set_static(const bool &);
            bool is_read_only() const;
            void set_read_only(const bool &);
            access_type get_visibility() const;
            void set_visibility(const access_type &);

            bool is_getter() const;
            void set_getter(bool, const member* const = nullptr); // member is optional if setting to false. member* can be a dynamic variable; we don't store its address: it is copied.
            bool is_setter() const;
            void set_setter(bool, const member* const = nullptr); // member is optional if setting to false. member* can be a dynamic variable; we don't store its address: it is copied.
            const member* get_getter_member() const;
            const member* get_setter_member() const;

        private:
            std::string _name;
            type_hint _return_type;
            std::map<std::string, type_hint> _params;
            bool _is_static = false; // static method
            bool _is_read_only = false; // think const keyword in C++
            access_type _visibility = VISIBLE_ACCESS; // think public, private, etc.

            member* _getter_member = nullptr;
            member* _setter_member = nullptr;
    };
}

#endif
