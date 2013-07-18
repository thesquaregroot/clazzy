
#include "h/language_factory.h"
#include "h/language_includes.h"
using namespace cranberry;
using namespace std;

language *language_factory::get_language(const string &name, mutex *io_mutex, bool debug_enabled)
{
        // DO NOT ADD NEW LANGUAGES HERE - USE mk_lang.sh
        if (name == "C++") {
                return new lang_cpp(io_mutex, debug_enabled);
        } else if (name == "C") {
                return new lang_c(io_mutex, debug_enabled);
        } else if (name == "Java") {
                return new lang_java(io_mutex, debug_enabled);
        // ### Language Instantiations ###
        } else {
                return 0;
        }
}
