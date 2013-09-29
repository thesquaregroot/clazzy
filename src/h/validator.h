#ifndef __CLAZZY_VALIDATOR__
#define __CLAZZY_VALIDATOR__

#include "class_def.h"
#include "type_hint.h"
#include <string>
#include <vector>
#include <unordered_set>

namespace clazzy {
    class validator {
        public:
            virtual std::string validate(class_def &);
            virtual std::string validate(std::vector<class_def> &);

        protected:
            std::string validate(const type_hint &);
            void add_type(const type_hint &);
            std::vector<type_hint> get_types();

        private:
            std::unordered_set<type_hint> _types_encountered;
    };
}

#endif
