#ifndef LANG_CPP_H
#define LANG_CPP_H

#include "language.h"
#include <vector>
#include <map>
#include <string>

namespace cranberry {
    class lang_cpp : public language {
        public:
            std::string get_name() const;
            void create(
                        const std::vector<class_def>&,
                        const std::map<std::string,std::string>&
                    ) const;
    };
}

#endif
