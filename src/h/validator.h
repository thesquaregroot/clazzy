#ifndef __CLAZZY_VALIDATOR__
#define __CLAZZY_VALIDATOR__

#include "class_def.h"
#include "type_hint.h"
#include <string>
#include <vector>

namespace clazzy {
    class validator {
        public:
            virtual std::string validate(class_def &);
            virtual std::string validate(std::vector<class_def> &);

        protected:
            std::string validate(const type_hint &);
            void add_type(const type_hint &);
            std::vector<type_hint> get_types();
            std::string handle_design_patterns(class_def&) const;

        private:
            std::vector<type_hint> _types_encountered;
    };
}

#endif
