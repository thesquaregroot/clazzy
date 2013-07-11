#ifndef MEMBER_H
#define MEMBER_H

#include <string>

namespace cranberry {
    class member {
        public:
            member(const std::string&);

            std::string get_name() const;

        private:
            std::string name;

    };
}

#endif
