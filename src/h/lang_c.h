#ifndef LANG_C_H
#define LANG_C_H

#include "language.h"
#include <vector>
#include <map>
#include <string>

namespace cranberry {
    class lang_c : public language {
        public:
            lang_c(std::mutex *io, bool debug) : language(io, debug) { }

            std::string get_name() const;
            void create(
                        const std::vector<class_def>&,
                        const std::map<std::string,std::string>&
                    ) const;
    };
}

#endif
