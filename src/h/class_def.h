#ifndef __CRANBERRY_CLASS_DEF_H__
#define __CRANBERRY_CLASS_DEF_H__

#include "type_hint.h"
#include <vector>
#include <string>

namespace cranberry {
    class method;
    class member;

    class class_def {
        public:
            class_def() {};
            class_def(const std::string&);

            void set_name(const std::string&);
            std::string get_name() const;

            // stores a class with a set of names parameters
            void add_method(method&);
            // stores a member variable name
            void add_member(member&);
            // stores a parent class/interface name
            void add_parent(type_hint&);
            // returns the map of method names to their parameters
            std::vector<method> get_methods() const;
            // gets the members of this class
            std::vector<member> get_members() const;
            // gets the parents of this class
            std::vector<type_hint> get_parents() const;

        private:
            std::string _name;
            // stores methods (name to parameter list mapping)
            std::vector<method> _methods;
            // stores member variables (names)
            std::vector<member> _members;
            // stores parent class names
            std::vector<type_hint> _parents;
    };
}

#endif
