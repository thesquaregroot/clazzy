#ifndef LANGUAGE_FACTORY_H
#define LANGUAGE_FACTORY_H

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
