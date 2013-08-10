#ifndef __CLAZZY_LANGUAGE_FACTORY_H__
#define __CLAZZY_LANGUAGE_FACTORY_H__

#include "language.h"
#include <string>
#include <mutex>

namespace clazzy {
    class language_factory {
        public:
            static language *get_language(const std::string&, std::mutex*, bool=false);
        private:
            language_factory() {}
    };
}

#endif
