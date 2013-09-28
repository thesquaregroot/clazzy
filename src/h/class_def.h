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
            class_def() = default;
            class_def(const std::string&);
            class_def(const class_def&);
            class_def(class_def &&);
            ~class_def();

            void set_name(const std::string&);
            std::string get_name() const;

            void add_constructor(constructor&);
            void set_explicit_destructor(const bool, const access_type * = nullptr);
            void add_method(method&);
            void add_member(member&);
            void add_parent(type_hint&);
            void add_design_pattern(design_pattern&);
            void set_referenced_types(const std::vector<type_hint> &);
            std::vector<constructor> get_constructors(const access_type * = nullptr) const;
            bool has_explicit_destructor() const;
            access_type *get_destructor_visibility() const;
            std::vector<method> get_methods(const access_type * = nullptr) const;
            std::vector<member> get_members(const access_type * = nullptr) const;
            std::vector<type_hint> get_parents() const;
            std::vector<type_hint> get_referenced_types() const;
            std::vector<design_pattern> get_design_patterns() const;

        private:
            std::string _name;
            // stores constructors/destructors
            std::map<access_type,std::vector<constructor>> _ctors;
            // true iff class should explictly define a destructor
            bool _has_destructor = false;
            access_type *_destructor_access = nullptr;
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
            
            // helper method for returning store vectors
            template<class T>
            std::vector<T> get(const std::map<access_type,std::vector<T>>&, const access_type *) const;
    };
}

#endif
