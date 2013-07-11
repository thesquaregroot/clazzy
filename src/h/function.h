#ifndef FUNCTION_H
#define FUNCTION_H

#include <vector>
#include <string>

namespace cranberry {
    class function {
        public:
            function(const std::string&);
            
            std::string get_name() const;
            void add_parameter(const std::string&);
            std::vector<std::string> get_parameters() const;

        private:
            std::string name;
            std::vector<std::string> params;
    };
}

#endif
