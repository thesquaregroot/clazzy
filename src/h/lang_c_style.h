#ifndef __CLAZZY_LANG_C_STYLE_H__
#define __CLAZZY_LANG_C_STYLE_H__

#include "language.h"
#include "type_convertor.h"
#include "access_type.h"
#include <fstream>
#include <vector>
#include <map>
#include <string>

namespace clazzy {
    class lang_c_style : public language {
        public:

            virtual std::string get_name() const override = 0;
            void create(
                        const std::vector<class_def>&,
                        const std::map<std::string,std::string>&
                    ) const override;

        protected:
            lang_c_style(std::mutex* io, bool debug) : language(io, debug) {} // abstract

            // returns the path a cpp file can use to include this class
            virtual std::string write_header(std::string /* base directory */, class_def&) const = 0;
            virtual void write_source(std::string /* base directory */, class_def&, std::string /* header path */) const = 0;

            virtual void print_parameters(std::ofstream&, parameterized * const) const;

            type_convertor types;
    };
}

#endif
