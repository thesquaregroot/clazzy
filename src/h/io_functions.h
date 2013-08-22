#ifndef __CLAZZY_IO_FUNCTIONS__
#define __CLAZZY_IO_FUNCTIONS__

#include <string>

namespace clazzy {
    // returns true iff:
    // - the path already exists and is a directory
    // - the path did not exist and a directory was created
    bool chk_mkdir(const std::string &);
}

#endif
