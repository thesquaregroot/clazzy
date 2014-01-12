
//
// DO NOT ADD NEW LANGUAGES HERE - USE mk_lang.sh
//

#include "language_factory.h"
#include "lang_cpp.h"
#include "lang_c.h"
#include "lang_java.h"
#include "lang_python.h"
// ### Language Includes ###
using namespace clazzy;
using namespace std;

language *language_factory::get_language(const string &name, mutex *io_mutex, bool debug_enabled)
{
        if (name == "C++") {
                return new lang_cpp(io_mutex, debug_enabled);
        } else if (name == "C") {
                return new lang_c(io_mutex, debug_enabled);
        } else if (name == "Java") {
                return new lang_java(io_mutex, debug_enabled);
        } else if (name == "Python") {
                return new lang_python(io_mutex, debug_enabled);
        // ### Language Instantiations ###
        } else {
                return 0;
        }
}

