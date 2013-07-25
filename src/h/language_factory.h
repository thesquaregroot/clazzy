#ifndef __CRANBERRY_LANGUAGE_FACTORY_H__
#define __CRANBERRY_LANGUAGE_FACTORY_H__

#include "language.h"
#include <string>
#include <mutex>

namespace cranberry {
    class language_factory {
        public:
            static language *get_language(const std::string&, std::mutex*, bool=false);
    };
}

#endif
