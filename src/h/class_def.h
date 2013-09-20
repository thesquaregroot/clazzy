#ifndef __CLAZZY_CLASS_DEF_H__
#define __CLAZZY_CLASS_DEF_H__

#include "constructor.h"
#include "type_hint.h"
#include "access_type.h"
#include "member.h"
#include "method.h"
#include "design_pattern.h"
#include <map>
#include <vector>
#include <string>

namespace clazzy {
    class class_def {
        public:
            class_def() {};
            class_def(const std::string&);

            void set_name(const std::string&);
            std::string get_name() const;

            // stores a constructor/destructor
            void add_constructor(constructor&);
            // stores a method
            void add_method(method&);
            // stores a member
            void add_member(member&);
            // stores a parent class/interface name
            void add_parent(type_hint&);
            // stores a design pattern
            void add_design_pattern(design_pattern&);
            // receive a list of referenced types
            void set_referenced_types(const std::vector<type_hint> &);
            // gets the constructors/destructors of this class
            std::vector<constructor> get_constructors(const access_type * = nullptr, short = ALL_CTORS) const;
            // gets the methods of this class
            std::vector<method> get_methods(const access_type * = nullptr) const;
            // gets the members of this class
            std::vector<member> get_members(const access_type * = nullptr) const;
            // gets the parents of this class
            std::vector<type_hint> get_parents() const;
            // return referenced types
            std::vector<type_hint> get_referenced_types() const;
            // return design patterns
            std::vector<design_pattern> get_design_patterns() const;

        private:
            static const short CTORS = 0x01;
            static const short DTORS = 0x02;
            static const short ALL_CTORS = CTORS & DTORS;
            std::string _name;
            // stores constructors/destructors
            std::map<access_type,std::vector<constructor>> _ctors;
            // stores methods (name to parameter list mapping)
            std::map<access_type,std::vector<method>> _methods;
            // stores member variables (names)
            std::map<access_type,std::vector<member>> _members;
            // stores parent class names
            std::vector<type_hint> _parents;
            // stores referenced types
            std::vector<type_hint> _referenced_types;
            // store design paterns
            std::vector<design_pattern> _design_patterns;
    };
}

#endif
