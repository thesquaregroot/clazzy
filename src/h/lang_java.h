#ifndef __CLAZZY_LANG_JAVA_H__
#define __CLAZZY_LANG_JAVA_H__

#include "language.h"
#include <vector>
#include <map>
#include <string>

namespace clazzy {
    class lang_java : public language {
        public:
            lang_java(std::mutex *io, bool debug) : language(io, debug) { }

            std::string get_name() const;
            void create(
                        const std::vector<class_def>&,
                        const std::map<std::string,std::string>&
                    ) const;
    };
}

#endif
