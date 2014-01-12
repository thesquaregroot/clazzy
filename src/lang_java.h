#ifndef __CLAZZY_LANG_JAVA_H__
#define __CLAZZY_LANG_JAVA_H__

#include "language.h"
#include "type_convertor.h"
#include "access_type.h"
#include <vector>
#include <map>
#include <string>

namespace clazzy {
    class lang_java : public language {
        public:
            lang_java(std::mutex *io, bool debug_enabled) : language(io, debug_enabled) { initialize(); }

            std::string get_name() const override;
            void create(
                        const std::vector<class_def>&,
                        const std::map<std::string,std::string>&
                    ) const override;

        private:
            void initialize();

            static std::map<access_type,std::string> access_prefixes;
            type_convertor types;
    };
}

#endif
