#ifndef TYPE_HINT_H
#define TYPE_HINT_H

#include <vector>
#include <string>

namespace cranberry {
    class type_hint {
        public:
            type_hint() {}
            type_hint(std::string, std::vector<type_hint>&);

            std::string get_base_type() const;
            std::vector<type_hint> get_generic_types() const;
            std::string to_string() const;
            
        private:
            bool is_primitive;
            std::string base_type;
            std::vector<type_hint> generic_types;
    };
}

#endif
