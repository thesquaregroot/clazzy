
#include "h/lang_python.h"
#include "h/io_functions.h"
#include "h/string_functions.h"
#include <vector>
#include <map>
#include <string>
#include <mutex>
using namespace clazzy;
using namespace std;

map<access_type,string> lang_python::access_prefixes = {
        {VISIBLE_ACCESS, ""},
        {HIDDEN_ACCESS, ""},
        {CHILD_VISIBLE_ACCESS, ""},
        {ASSEMBLY_VISIBLE_ACCESS, ""}
};

string lang_python::get_name() const
{
        return "Python";
}

void lang_python::initialize()
{
        // TODO: create mappings and add any additional
        types.add_type("byte", "");
        types.add_type("short", "");
        types.add_type("integer", "");
        types.add_type("long", "");
        types.add_type("character", "");
        types.add_type("string", "");
        types.add_type("float", "");
        types.add_type("double", "");
        types.add_type("boolean", "");
        types.add_type("void", "");
}

void lang_python::create(
                        const vector<class_def> &classes,
                        const map<string,string> &properties
        ) const
{
        // create directory
        string base_dir = "./clazzy_python/";
        if (!chk_mkdir(base_dir)) {
                error("Failure creating directory: " + base_dir);
        }
        // create class files
        for (const class_def &c : classes) {
                ofstream out;
                string file_name = base_dir + to_full_camel_case(c.get_name()) + ".py";
                if (!open_file(file_name, out, "#")) {
                        error("Failure creating file: " + file_name);
                }
                // class definition
                out << endl;
                out << "class " << to_full_camel_case(c.get_name());
                // parents
                vector<type_hint> parents = c.get_parents();
                if (parents.size() > 0) {
                        out << "(";
                        for (unsigned int i=0; i<parents.size(); i++) {
                                type_hint t = parents[i];
                                out << types.convert_cc(t);
                                if (i != parents.size()-1) {
                                       out << ", "; 
                                }
                        }
                        out << ")";
                }
                out << ":" << endl;
                // class body
                for (method m : c.get_methods()) {
                        out << language::TWO_SPACES;
                        out << m.get_name();
                        out << "(self";
                        for (auto param : m.get_parameters()) {
                                out << ", " << param.first;
                        }
                        out << "):" << endl;
                        out << language::FOUR_SPACES << "# TODO: Implement" << endl;
                        out << language::TWO_SPACES << endl;
                }
                out << endl;
        }
}

