#ifndef CLAZZY_IO_HELPERS_H
#define CLAZZY_IO_HELPERS_H

#include <ostream>
#include <fstream>
#include <vector>
#include "Class.h"

namespace clazzy {

    //// For IR Files:
    ////////////////////

    // Serializes the supplied <classes> into <file>.
    //
    // Will overwrite an existing file iff <overwrite> is true (default).
    //
    // Returns true iff the file was written to successfully.
    bool write(std::vector<Class> classes, const std::string& file, bool overwrite = true);

    // Creates a vector of Class objects from the contents of <file>.
    //
    // If the file cannot be read or if the file does not contain an
    //  appropriate definition, an empty vector will be returned and
    //  an error message printed.
    std::vector<Class> read(const std::string& file);

    //// For Language Files:
    //////////////////////////

    // returns true iff:
    // - the path already exists and is a directory
    // - the path did not exist and a directory was created
    bool chk_mkdir(const std::string&);

    // does the following
    // - creates or opens a file into the passed ofstream object (if it cannot, returns false)
    // - writes a notification at the top of the file using the given comment characters
    // - returns true (assuming the rest went well)
    bool open_file(const std::string&, std::ofstream&, const std::string&);
}

#endif // CLAZZY_IO_HELPERS_H
