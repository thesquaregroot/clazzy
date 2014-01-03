#ifndef __CLAZZY_LANG_C_H__
#define __CLAZZY_LANG_C_H__

#include "lang_c_style.h"
#include "type_convertor.h"
#include "access_type.h"
#include <vector>
#include <map>
#include <string>

namespace clazzy {
    class lang_c : public lang_c_style {
        public:
            lang_c(std::mutex* io, bool debug) : lang_c_style(io, debug) { initialize(); }

            std::string get_name() const override;

        protected:
            // returns the path a cpp file can use to include this class
            virtual std::string write_header(std::string /* base directory */, class_def&) const override;
            virtual void write_source(std::string /* base directory */, class_def&, std::string /* header path */) const override;

            static std::map<access_type, std::string> access_prefixes;

        private:
            void initialize();
    };
}

#endif
