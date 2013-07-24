#ifndef TYPE_UTIL_H
#define TYPE_UTIL_H

#include <string>
#include <map>
#include <set>

namespace cranberry {
    enum type : unsigned short;

    class type_util {
        public:
            bool add_type(const std::string &);
            
            bool is_defined(const std::string &) const;
            bool is_generic(const std::string &) const;
            bool is_primitive(const std::string &) const;
            bool is_user_type(const std::string &) const;

        private:
            static const std::map<std::string,type> generics;
            static const std::map<std::string,type> primitives;
            std::set<std::string> user_types;
    };
}

#endif
