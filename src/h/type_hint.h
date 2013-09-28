#ifndef __CLAZZY_TYPE_HINT_H__
#define __CLAZZY_TYPE_HINT_H__

#include <vector>
#include <string>

namespace clazzy {
    class type_hint {
        public:
            type_hint() = default;
            type_hint(const type_hint&) = default;
            type_hint(std::string, const std::vector<type_hint>& = std::vector<type_hint>());

            std::string get_base_type() const;
            std::vector<type_hint> get_generic_types() const;
            std::string to_string() const;

            bool operator==(const type_hint &) const;
            bool operator!=(const type_hint &) const;
            
        private:
            std::string _base_type;
            std::vector<type_hint> _generic_types;
    };
}

#endif
