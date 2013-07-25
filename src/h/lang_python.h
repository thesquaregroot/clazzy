#ifndef __CRANBERRY_LANG_PYTHON_H__
#define __CRANBERRY_LANG_PYTHON_H__

#include "language.h"
#include <vector>
#include <map>
#include <string>

namespace cranberry {
    class lang_python : public language {
        public:
            lang_python(std::mutex *io, bool debug) : language(io, debug) { }

            std::string get_name() const;
            void create(
                        const std::vector<class_def>&,
                        const std::map<std::string,std::string>&
                    ) const;
    };
}

#endif
