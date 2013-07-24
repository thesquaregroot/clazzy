#ifndef CLASS_DEF_H
#define CLASS_DEF_H

#include "type_hint.h"
#include <vector>
#include <string>

namespace cranberry {
    class function;
    class member;

    class class_def {
        public:
            class_def() {};
            class_def(const std::string&);

            void set_name(const std::string&);
            std::string get_name() const;

            // stores a class with a set of names parameters
            void add_function(function&);
            // stores a member variable name
            void add_member(member&);
            // stores a parent class/interface name
            void add_parent(type_hint&);
            // returns the map of function names to their parameters
            std::vector<function> get_functions() const;
            // gets the members of this class
            std::vector<member> get_members() const;
            // gets the parents of this class
            std::vector<type_hint> get_parents() const;

        private:
            std::string name;
            // stores functions (name to parameter list mapping)
            std::vector<function> functions;
            // stores member variables (names)
            std::vector<member> members;
            // stores parent class names
            std::vector<type_hint> parents;
    };
}

#endif
