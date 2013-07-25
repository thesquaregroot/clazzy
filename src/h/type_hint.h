#ifndef __CRANBERRY_TYPE_HINT_H__
#define __CRANBERRY_TYPE_HINT_H__

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
            std::string _base_type;
            std::vector<type_hint> _generic_types;
    };
}

#endif
