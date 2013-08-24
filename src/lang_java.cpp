
#include "h/lang_java.h"
#include "h/io_functions.h"
#include <vector>
#include <map>
#include <string>
using namespace clazzy;
using namespace std;

map<access_type,string> lang_java::access_prefixes = {
        {VISIBLE_ACCESS, "public "},
        {HIDDEN_ACCESS, "private "},
        {CHILD_VISIBLE_ACCESS, "protected "},
        {ASSEMBLY_VISIBLE_ACCESS, ""}
};

void lang_java::initialize()
{
        types.add_type("byte", "byte");
        types.add_type("short", "short");
        types.add_type("integer", "int");
        types.add_type("long", "long");
        types.add_type("character", "char");
        types.add_type("string", "String");
        types.add_type("float", "float");
        types.add_type("double", "double");
        types.add_type("boolean", "boolean");
        types.add_type("void", "void");
}

string lang_java::get_name() const
{
        return "Java";
}

void lang_java::create(
                        const vector<class_def> &classes,
                        const map<string,string> &properties
        ) const
{
        string base_dir = "./clazzy_java/";
        string default_package = "com.clazzy";
        // create main directory
        if (!chk_mkdir(base_dir)) {
                error("Could not create directory " + base_dir + ".");
        }
        // get package
        string package = default_package;
        if (properties.find("JAVA_PACKAGE") != properties.end()) {
                package = properties.find("JAVA_PACKAGE")->second;
        }
        // create package directories
        string dir = base_dir;
        for (unsigned int i=0; i<package.size(); i++) {
                while (package[i] != '.' && i < package.size()) {
                        dir += package[i++];
                }
                dir += '/';
                if (!chk_mkdir(dir)) {
                        error("Could not create directory " + dir + ".");
                }
        }
        // TODO: implement
}

