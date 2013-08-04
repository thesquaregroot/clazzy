
#include "h/lang_cpp.h"
#include "h/class_def.h"
#include "h/method.h"
#include "h/member.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <string>
#include <mutex>
#include <cctype>
#include <sys/stat.h>
using namespace cranberry;
using namespace std;

map<access_type,string> lang_cpp::access_prefixes = {
        {VISIBLE_ACCESS, "public"},
        {ASSEMBLY_VISIBLE_ACCESS, "public"},
        {CHILD_VISIBLE_ACCESS, "protected"},
        {HIDDEN_ACCESS, "private"}
};

string lang_cpp::get_name() const
{
        return "C++";
}

void lang_cpp::write_header(string base_dir, class_def &c) const
{
        string header_dir = base_dir + "h/";
        struct stat sb;
        if (stat(header_dir.c_str(), &sb) != 0 && !S_ISDIR(sb.st_mode)) {
                if (mkdir(header_dir.c_str(), S_IRWXU|S_IRWXG) != 0) {
                        error("Could not create directory: " + header_dir);
                }
        }
        string path = header_dir + c.get_name() + ".h";
        ofstream out(path);

        if (!out.is_open()) {
                error("Could not open file: " + path);
                return;
        }
        
        string class_name = c.get_name();
        string include_guard = "__";
        for (unsigned int i=0; i<class_name.size(); i++) {
                include_guard += toupper(class_name[i]);
        }
        include_guard += "_H__";
        out << "#ifndef " << include_guard << endl;
        out << "#define " << include_guard << endl;
        out << endl;
        // TODO: Includes?--Use validator?
        // start class definition and inherit from parents
        
        write_cranberry_notice(out, "//");

        out << "class " << c.get_name();
        vector<type_hint> parents = c.get_parents();
        if (parents.size() > 0) {
                out << " : ";
                for (unsigned int i=0; i<parents.size(); i++) {
                        type_hint t = parents[i];
                        out << "public " << types.convert(t);
                        if (i < parents.size()-1) {
                                out << ", ";
                        }
                }
        }
        out << " {" << endl;
        // begin definitions
        for (auto it = access_prefixes.cbegin(); it != access_prefixes.cend(); it++) {
                // get method & members
                vector<method> methods = c.get_methods(&it->first);
                vector<member> members = c.get_members(&it->first);
                if (methods.size() == 0 && members.size() == 0) {
                        // not methods or members--move on to next access level
                        continue;
                }
                // print prefix
                out << language::FOUR_SPACES << it->second << ":" << endl;
                for (method m : methods) {
                        out << language::EIGHT_SPACES;
                        if (m.is_static()) {
                                out << "static ";
                        }
                        out << types.convert(m.get_return_type());
                        out << " " << m.get_name();
                        out << "(";
                        map<string,type_hint> params = m.get_parameters();
                        for (auto param_it = params.cbegin(); param_it != params.cend(); param_it++) {
                                // TODO: parameter modifiers
                                // map string -> type_hint
                                out << types.convert(param_it->second) << " " << param_it->first;
                                if (param_it != --params.cend()) {
                                        out << ", ";
                                }
                        }
                        out << ")";
                        if (m.is_read_only()) {
                                out << " const";
                        }
                        out << ";" << endl;
                        if (members.size() > 0) {
                                out << endl; // extra new line
                        }
                }
                // members
                for (member m : members) {
                        out << language::EIGHT_SPACES;
                        if (m.is_static()) {
                                out << "static ";
                        }
                        if (m.is_constant()) {
                                out << "const ";
                        }       
                        out << types.convert(m.get_type());
                        out << " " << m.get_name();
                        out << ";" << endl;
                }
                out << endl; // new line after access level
        }

        // end class definition
        out << "};" << endl;
        out << endl;
        out << "#endif" << endl;
}

void lang_cpp::write_cpp(string base_dir, class_def &c) const
{
        string path = base_dir + c.get_name() + ".cpp";
        ofstream out(path);
        
        if (!out.is_open()) {
                error("Could not open file: " + path);
        }

        out << endl;
        write_cranberry_notice(out, "//");
        
        out << "using namespace std;" << endl;
        out << endl;
        for (method m : c.get_methods()) {
                out << types.convert(m.get_return_type()) << " ";
                out << c.get_name() << "::" << m.get_name();
                out << "(";
                auto params = m.get_parameters();
                for (auto param = params.cbegin(); param != params.cend(); param++) {
                        // TODO: parameter modifiers
                        out << types.convert(param->second) << " " << param->first;
                        if (param != --params.cend()) {
                               out << ", ";
                        }
                }
                out << ")";
                out << endl;
                out << language::EIGHT_SPACES;
                out << "// TODO: implement";
                out << endl;
                out << "}" << endl;
                out << endl;
        }
}

void lang_cpp::initialize()
{
        types.add_type("byte", "char");
        types.add_type("short", "short");
        types.add_type("integer", "int");
        types.add_type("long", "long");
        types.add_type("character", "char");
        types.add_type("string", "std::string");
        types.add_type("float", "float");
        types.add_type("double", "double");
        types.add_type("boolean", "bool");
        types.add_type("void", "void");
}

void lang_cpp::create(
                        const vector<class_def> &classes,
                        const map<string,string> &properties
        ) const
{
        for (class_def c : classes) {
                debug("Creating code for class: " + c.get_name());
                string base_dir = "./cran_cpp/";
                struct stat sb;
                if (stat(base_dir.c_str(), &sb) != 0 || !S_ISDIR(sb.st_mode)) {
                        if (mkdir(base_dir.c_str(), S_IRWXU|S_IRWXG) != 0) {
                                error("Could not create directory: " + base_dir);
                        }
                }
                write_header(base_dir, c);
                write_cpp(base_dir, c);
        }
}
