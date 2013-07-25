#ifndef __CRANBERRY_METHOD_H__
#define __CRANBERRY_METHOD_H__

#include "type_hint.h"
#include "access_type.h"
#include <map>
#include <string>

namespace cranberry {
    class method {
        public:
            method(type_hint, std::string);
            
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

        private:
            std::string _name;
            type_hint _return_type;
            std::map<std::string, type_hint> _params;
            bool _is_static = false; // static method
            bool _is_read_only = false; // think const keyword in C++
            access_type _visibility = VISIBLE; // think public, private, etc.
    };
}

#endif
