#ifndef LANG_JAVA_H
#define LANG_JAVA_H

#include "language.h"
#include <vector>
#include <map>
#include <string>

namespace cranberry {
    class lang_java : public language {
        public:
            lang_java(std::mutex *io) : language(io) { }

            std::string get_name() const;
            void create(
                        const std::vector<class_def>&,
                        const std::map<std::string,std::string>&
                    ) const;
    };
}

#endif
