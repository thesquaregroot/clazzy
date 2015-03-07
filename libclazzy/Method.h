#ifndef CLAZZY_METHOD_H
#define CLAZZY_METHOD_H

#include <string>
#include "Argument.h"
#include "Type.h"
#include "AccessLevel.h"

namespace clazzy {

    class Method {
    public:
        Method(const std::string& name);

        //// High Level Definition
        std::string get_name() const;
        void        set_name(const std::string&);

        //// Access
        bool is_abstract() const;
        void set_abstract(bool);

        bool is_static() const;
        void set_static(bool);

        bool is_read_only() const;
        void set_read_only(bool);

        bool is_final() const;
        void set_final(bool);

        AccessLevel get_access_level() const;
        void        set_access_level(const AccessLevel&);

        //// Arguments and Return Type
        std::vector<Argument> get_arguments() const;
        void                  add_argument(const Argument&);

        Type get_return_type() const;
        void set_return_type(const Type&);

        //// Documentation methods
        std::string get_doc_short() const;
        void        set_doc_short(const std::string&);

        std::string get_doc_detail() const;
        void        set_doc_detail(const std::string&);

    private:
        std::string             _name;
        bool                    _is_abstract;
        bool                    _is_static;
        bool                    _is_read_only;
        bool                    _is_final;
        AccessLevel             _access_level;
        std::vector<Argument>   _arguments;
        Type                    _return_type;
        std::string             _doc_short;
        std::string             _doc_detail;
    };

}

#endif //CLAZZY_METHOD_H
