
#include "io_helpers.h"
#include <sys/stat.h>
#include <map>
using namespace clazzy;
using namespace std;

const char CLAZZY_DELIMITER = '|';

const char MODIFIER_CHAR_PUBLIC      = 'p';
const char MODIFIER_CHAR_PROTECTED   = 't';
const char MODIFIER_CHAR_PRIVATE     = 'v';
const char MODIFIER_CHAR_ABSTRACT    = 'a';
const char MODIFIER_CHAR_STATIC      = 's';
const char MODIFIER_CHAR_READ_ONLY   = 'r';
const char MODIFIER_CHAR_FINAL       = 'f';

const map<AccessLevel, char> ACCESS_LEVEL_MODIFIERS = {
    {AccessLevel::PUBLIC,       MODIFIER_CHAR_PUBLIC},
    {AccessLevel::PROTECTED,    MODIFIER_CHAR_PROTECTED},
    {AccessLevel::PRIVATE,      MODIFIER_CHAR_PRIVATE}
};

bool write_class(ofstream&, const Class&);
bool write_method(ofstream&, const Method&);
bool write_argument(ofstream&, const Argument&);
bool write_member(ofstream&, const Member&);

bool write_class(ofstream& out, const Class& clazz) {
    out << "C" << CLAZZY_DELIMITER;
    // name
    out << clazz.get_name() << CLAZZY_DELIMITER;
    // parents
    auto parents = clazz.get_parents();
    for (size_t i=0; i<parents.size(); i++) {
        if (i != 0) {
            out << ',';
        }
        out << parents[i].to_string();
    }
    // design patterns
    auto patterns = clazz.get_design_patterns();
    for (size_t i=0; i<patterns.size(); i++) {
        if (i != 0) {
            out << ',';
        }
        out << to_string(patterns[i]);
    }
    // access
    out << ACCESS_LEVEL_MODIFIERS.find(clazz.get_access_level())->second;
    if (clazz.is_final()) {
        out << MODIFIER_CHAR_FINAL;
    }
    out << CLAZZY_DELIMITER;
    // generics
    out << clazz.get_generics_count();
    out << CLAZZY_DELIMITER;
    // namespace
    out << clazz.get_namespace();
    out << CLAZZY_DELIMITER;
    // package
    out << clazz.get_package();
    out << endl;
    // end of class records, write other components
    for (const Method& method : clazz.get_methods()) {
        if (!write_method(out, method)) {
            return false;
        }
    }
    for (const Member& member : clazz.get_members()) {
        if (!write_member(out, member)) {
            return false;
        }
    }
    return true;
}
bool write_method(ofstream& out, const Method& method) {
    out << "M" << CLAZZY_DELIMITER;
    // name
    out << method.get_name();
    out << CLAZZY_DELIMITER;
    // access
    if (method.is_static()) {
        out << MODIFIER_CHAR_STATIC;
    }
    if (method.is_read_only()) {
        out << MODIFIER_CHAR_READ_ONLY;
    }
    if (method.is_final()) {
        out << MODIFIER_CHAR_FINAL;
    }
    out << CLAZZY_DELIMITER;
    // return type
    out << method.get_return_type().to_string();
    out << endl;
    // arguments
    for (const Argument& argument : method.get_arguments()) {
        if (!write_argument(out, argument)) {
            return false;
        }
    }
    return true;
}
bool write_argument(ofstream& out, const Argument& argument) {
    out << "a" << CLAZZY_DELIMITER;
    // name
    out << argument.get_name();
    out << CLAZZY_DELIMITER;
    // access
    if (argument.is_read_only()) {
        out << MODIFIER_CHAR_READ_ONLY;
    }
    out << CLAZZY_DELIMITER;
    // default value
    out << argument.get_default_value();
    out << endl;
    return true;
}
bool write_member(ofstream& out, const Member& member) {
    out << "m" << CLAZZY_DELIMITER;
    // name
    out << member.get_name();
    out << CLAZZY_DELIMITER;
    // access
    out << ACCESS_LEVEL_MODIFIERS.find(member.get_access_level())->second;
    if (member.is_static()) {
        out << MODIFIER_CHAR_STATIC;
    }
    if (member.is_read_only()) {
        out << MODIFIER_CHAR_READ_ONLY;
    }
    out << CLAZZY_DELIMITER;
    // type
    out << member.get_type().to_string();
    out << CLAZZY_DELIMITER;
    // default value
    out << member.get_default_value();
    out << endl;
    return true;
}

bool clazzy::write(vector<Class> classes, const string& file, bool overwrite) {
    if (file_exists(file) && !overwrite) {
        return false;
    }
    // file does not exist and/or we are allowed to overwrite it
    ofstream out;
    out.open(file);
    if (!out.is_open()) {
        return false;
    }
    for (const Class& clazz : classes) {
        write_class(out, clazz);
    }
    return true;
}

vector<Class> clazzy::read(const string& file) {
    vector<Class> classes;
    ifstream in;
    in.open(file);
    if (!in.is_open()) {
        return classes;
    }
    // TODO: populate
    return classes;
}

bool clazzy::file_exists(const string& file) {
    ifstream in(file);
    return in.good();
}

bool clazzy::chk_mkdir(const string& dir_name)
{
    struct stat sb;
    if (stat(dir_name.c_str(), &sb) != 0 && !S_ISDIR(sb.st_mode)) {
        return (mkdir(dir_name.c_str(), S_IRWXU|S_IRWXG) == 0);
    } else {
        return true;
    }
}

bool clazzy::open_file(const string& path, ofstream& out, const string& comment_chars)
{
    out.open(path);
    if (!out.is_open()) {
        return false;
    }
    out << comment_chars << endl;
    out << comment_chars << " This code was generated by clazzy (https://github.com/thesquaregroot/clazzy)." << endl;
    out << comment_chars << endl;
    return true;
}

