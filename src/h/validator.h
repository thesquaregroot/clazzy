#ifndef __CLAZZY_VALIDATOR__
#define __CLAZZY_VALIDATOR__

#include "class_def.h"
#include "type_hint.h"
#include <vector>

namespace clazzy {
    class validator {
        public:
            virtual void validate(class_def &);
            virtual void validate(std::vector<class_def> &);

        protected:
            void add_type(const type_hint &);
            std::vector<type_hint> get_types();

        private:
            std::vector<type_hint> types_encountered;
    };
}

#endif
