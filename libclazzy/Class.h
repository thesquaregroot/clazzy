#ifndef CLAZZY_CLASS_H
#define CLAZZY_CLASS_H

#include <string>
#include "Method.h"
#include "Member.h"
#include "Type.h"
#include "DesignPattern.h"
#include "AccessLevel.h"

namespace clazzy {

    class Class {
    public:
        Class(const std::string& name);

        //// High Level Definition
        std::string get_name() const;
        void        set_name(const std::string&);

        std::vector<Type> get_parents() const;
        void              add_parent(const Type&);

        std::vector<DesignPattern> get_design_patterns() const;
        void                       add_design_pattern(const DesignPattern&);

        // returns true iff there is an abstract method present
        bool is_abstract() const;
        // returns true iff there are no:
        //   - non-static members
        //   - non-abstract methods
        //   - constructors or destructors
        bool is_interface() const;

        int  get_generics_count() const;
        void set_generics_count(int);

        //// Access
        bool is_final() const;
        void set_final(bool);

        AccessLevel get_access_level() const;
        void        set_access_level(const AccessLevel&);

        //// Namespaces and Packages
        std::string get_namespace() const;
        void        set_namespace(const std::string&);

        std::string get_package() const;
        void        set_package(const std::string&);

        //// Methods and Members
        std::vector<Method> get_methods() const;
        void                add_method(const Method&);

        std::vector<Member> get_members() const;
        void                add_member(const Member&);

        //// Documentation methods
        std::string get_doc_short() const;
        void        set_doc_short(const std::string&);

        std::string get_doc_detail() const;
        void        set_doc_detail(const std::string&);

    private:
        std::string                 _name;
        std::vector<Type>           _parents;
        std::vector<DesignPattern>  _design_patterns;
        bool                        _is_final = false;
        AccessLevel                 _access_level = AccessLevel::PUBLIC;
        std::string                 _namespace;
        std::string                 _package;
        int                         _generics_count;
        std::vector<Method>         _methods;
        std::vector<Member>         _members;
        std::string                 _doc_short;
        std::string                 _doc_detail;
    };

}

#endif //CLAZZY_CLASS_H
