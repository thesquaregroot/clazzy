#ifndef __CLAZZY_LANG_CPP_H__
#define __CLAZZY_LANG_CPP_H__

#include "language.h"
#include "type_convertor.h"
#include "access_type.h"
#include <vector>
#include <map>
#include <string>

namespace clazzy {
    class lang_cpp : public language {
        public:
            lang_cpp(std::mutex *io, bool debug) : language(io, debug) { initialize(); }

            std::string get_name() const;
            void create(
                        const std::vector<class_def>&,
                        const std::map<std::string,std::string>&
                    ) const;
        
        private:
            void initialize();

            // returns the path a cpp file can use to include this class
            std::string write_header(std::string /* base directory */, class_def&) const;
            void write_cpp(std::string /* base directory */, class_def&, std::string /* header path */) const;

            static std::map<access_type,std::string> access_prefixes;
            type_convertor types;
    };
}

#endif
