#ifndef MEMBER_H
#define MEMBER_H

#include "type_hint.h"
#include <string>

namespace cranberry {
    class member {
        public:
            member(const type_hint &, const std::string &);

            std::string get_name() const;
            type_hint get_type() const;

        private:
            std::string name;
            type_hint type;
    };
}

#endif
