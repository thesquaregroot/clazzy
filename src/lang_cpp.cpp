
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

string lang_cpp::get_name() const
{
        return "C++";
}

void lang_cpp::write_header(string base_dir, class_def &c) const
{
        string header_dir = base_dir + "h/";
        if (mkdir(header_dir.c_str(), S_IRWXU|S_IRWXG) != 0) {
                error("Could not create directory: " + header_dir);
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
                        // TODO: Convert to C++ type
                        out << "public " << t.to_string();
                        if (i < parents.size()-1) {
                                out << ", ";
                        }
                }
        }
        out << " {" << endl;
        // begin definitions
        // public
        out << language::FOUR_SPACES << "public:" << endl;
        // methods
        vector<method> methods = c.get_methods();
        vector<member> members = c.get_members();
        for (method m : methods) {
                out << language::EIGHT_SPACES;
                if (m.is_static()) {
                        out << "static ";
                }
                // TODO: Convert to C++ type
                out << m.get_return_type().to_string();
                out << " " << m.get_name();
                out << "(";
                map<string,type_hint> params = m.get_parameters();
                for (auto it = params.cbegin(); it != params.cend(); it++) {
                        // map string -> type_hint
                        out << it->second.to_string() << " " << it->first;
                        if (it != --params.cend()) {
                                out << ", ";
                        }
                }
                out << ")";
                if (m.is_read_only()) {
                        out << " const";
                }
                out << ";" << endl;
        }
        if (methods.size() > 0) {
                out << endl; // extra new line
        }
        // members
        for (member m : members) {
                out << language::EIGHT_SPACES;
                // TODO: Convert to C++ type
                if (m.is_static()) {
                        out << "const ";
                }
                out << m.get_type().to_string();
                out << " " << m.get_name();
                out << ";" << endl;
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
}


void lang_cpp::create(
                        const vector<class_def> &classes,
                        const map<string,string> &properties
        ) const
{
        for (class_def c : classes) {
                debug("Creating code for class: " + c.get_name());
                string base_dir = "./cpp/";
                if (mkdir(base_dir.c_str(), S_IRWXU|S_IRWXG) != 0) {
                        error("Could not create directory: " + base_dir);
                }
                write_header(base_dir, c);
                write_cpp(base_dir, c);
        }
}
