#ifndef CLAZZY_MEMBER_H
#define CLAZZY_MEMBER_H

#include <string>
#include "Type.h"
#include "AccessLevel.h"

namespace clazzy {

    class Member {
    public:
        Member(const std::string& name);

        //// High Level Definition
        std::string get_name() const;
        void        set_name(const std::string&);

        //// Access
        bool is_static() const;
        void set_static(bool);

        bool is_read_only() const;
        void set_read_only();

        bool is_final() const;
        void set_final(bool);

        AccessLevel get_access_level() const;
        void        set_access_level(const AccessLevel&);

        //// Type
        Type get_type() const;
        void set_type(const Type&);

        //// Documentation methods
        std::string get_doc_short() const;
        void        set_doc_short(const std::string&);

        std::string get_doc_detail() const;
        void        set_doc_detail(const std::string&);

    private:
        std::string             _name;
        bool                    _is_static;
        bool                    _is_read_only;
        bool                    _is_final;
        AccessLevel             _access_level;
        Type                    _type;
        std::string             _doc_short;
        std::string             _doc_detail;
    };

}

#endif //CLAZZY_MEMBER_H
