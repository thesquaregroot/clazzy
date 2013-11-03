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

            // constructor/destructor
            void add_constructor(const constructor&);
            std::vector<constructor> get_constructors(const access_type * = nullptr) const;
            void set_explicit_destructor(const bool, const access_type * = nullptr);
            bool has_explicit_destructor() const;
            access_type *get_destructor_visibility() const;
            // methods
            void add_method(const method&);
            std::vector<method> get_methods(const access_type * = nullptr) const;
            std::vector<method> get_static_methods(const access_type * = nullptr) const;
            // members
            void add_member(const member&);
            std::vector<member> get_members(const access_type * = nullptr) const;
            std::vector<member> get_static_members(const access_type * = nullptr) const;
            // parents
            void add_parent(const type_hint&);
            std::vector<type_hint> get_parents() const;
            // referenced types
            void set_referenced_types(const std::vector<type_hint> &);
            std::vector<type_hint> get_referenced_types() const;
            // design patterns
            void add_design_pattern(const design_pattern&);
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
            template<class T = declarable>
            std::vector<T> get_static(const std::map<access_type,std::vector<T>>&, const access_type *) const;
    };
}

#endif
