#ifndef FUNCTION_H
#define FUNCTION_H

#include "type_hint.h"
#include <map>
#include <string>

namespace cranberry {
    class function {
        public:
            function(type_hint, std::string);
            
            std::string get_name() const;
            type_hint get_return_type() const;
            void add_parameter(type_hint, std::string);
            std::map<std::string, type_hint> get_parameters() const;

        private:
            std::string name;
            type_hint return_type;
            std::map<std::string, type_hint> params;
    };
}

#endif
