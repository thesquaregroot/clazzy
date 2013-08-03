#ifndef __CRANBERRY_LANG_CPP_H__
#define __CRANBERRY_LANG_CPP_H__

#include "language.h"
#include <vector>
#include <map>
#include <string>

namespace cranberry {
    class lang_cpp : public language {
        public:
            lang_cpp(std::mutex *io, bool debug) : language(io, debug) { }

            std::string get_name() const;
            void create(
                        const std::vector<class_def>&,
                        const std::map<std::string,std::string>&
                    ) const;
        
        private:
            void write_header(std::string, class_def&) const;
            void write_cpp(std::string, class_def&) const;
    };
}

#endif
