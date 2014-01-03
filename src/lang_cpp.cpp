
#include "h/lang_cpp.h"
#include "h/class_def.h"
#include "h/method.h"
#include "h/member.h"
#include "h/io_functions.h"
#include <unordered_set>
#include <vector>
#include <map>
#include <string>
#include <mutex>
#include <cctype>
using namespace clazzy;
using namespace std;

map<access_type,string> lang_cpp::access_prefixes = {
        {VISIBLE_ACCESS, "public"},
        {ASSEMBLY_VISIBLE_ACCESS, "public"},
        {CHILD_VISIBLE_ACCESS, "protected"},
        {HIDDEN_ACCESS, "private"}
};

void lang_cpp::initialize()
{
        types.add_type("byte", "char");
        types.add_type("short", "short");
        types.add_type("integer", "int");
        types.add_type("long", "long");
        types.add_type("character", "char");
        types.add_type("string", "std::string", new string("<string>"));
        types.add_type("float", "float");
        types.add_type("double", "double");
        types.add_type("boolean", "bool");
        types.add_type("void", "void");
        // container types
        //types.add_type("array", "");
        //types.add_type("deque", "");
        types.add_type("list", "std::vector", new string("<vector>"));
        types.add_type("set", "std::set", new string("<set>"));
        types.add_type("stack", "std::stack", new string("<stack>"));
        types.add_type("queue", "std::queue", new string("<queue>"));
        types.add_type("map", "std::map", new string("<map>"));
        //types.add_type("pointer", "");
}

string lang_cpp::get_name() const
{
        return "C++";
}

string lang_cpp::get_simple_name() const
{
        return "cpp";
}

string lang_cpp::write_header(string base_dir, class_def &c) const
{
        string header_dir = base_dir + "h/";
        if (!chk_mkdir(header_dir)) {
                error("Could not create directory: " + header_dir);
        }
        string include_path = "h/" + c.get_name() + ".h";
        string path = base_dir + include_path;
        ofstream out;
        if (!open_file(path, out, "//")) {
                error("Could not open file: " + path);
                return include_path;
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

        // includes
        vector<string> imports = types.get_imports(c.get_referenced_types());
        for (const string &header : imports) {
                out << "#include " << header << endl;
        }
        if (imports.size() > 0) {
                out << endl;
        }

        // start class definition and inherit from parents        
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
                vector<constructor> ctors = c.get_constructors(&it->first);
                vector<method> methods = c.get_methods(&it->first);
                vector<member> members = c.get_members(&it->first);
                bool valid_destructor = false;
                if (c.has_explicit_destructor()) {
                        access_type *dtor_access = c.get_destructor_visibility();
                        // conditions for destructor for this access level:
                        //  - no access defined, default to public
                        //  - access defined and we're in that iteration
                        valid_destructor = (dtor_access == nullptr && it->first == VISIBLE_ACCESS)
                                        || (dtor_access != nullptr && it->first == *dtor_access);
                }
                if (ctors.size() == 0 && !valid_destructor && methods.size() == 0 && members.size() == 0) {
                        // nothing here--move on to next access level
                        continue;
                }
                // print prefix
                out << language::FOUR_SPACES << it->second << ":" << endl;
                // constructors
                for (constructor ctor : ctors) {
                        out << language::EIGHT_SPACES;
                        out << c.get_name();
                        out << "(";
                        print_parameters(out, &ctor);
                        out << ");" << endl;
                }
                if (valid_destructor) {
                        out << language::EIGHT_SPACES;
                        out << "~" << c.get_name();
                        out << "();" << endl;
                }
                // optional extra newline
                if (ctors.size() > 0 || valid_destructor) {
                        out << endl;
                }
                //methods
                for (method m : methods) {
                        out << language::EIGHT_SPACES;
                        if (m.is_static()) {
                                out << "static ";
                        }
                        out << types.convert(m.get_return_type());
                        out << " " << m.get_name();
                        out << "(";
                        print_parameters(out, &m);
                        out << ")";
                        if (m.is_read_only()) {
                                out << " const";
                        }
                        out << ";" << endl;
                }
                // optional extra newline
                if (methods.size() > 0) {
                        out << endl;
                }
                // members
                for (member m : members) {
                        out << language::EIGHT_SPACES;
                        if (m.is_static()) {
                                out << "static ";
                        }
                        if (m.is_read_only()) {
                                out << "const ";
                        }
                        out << types.convert(m.get_type());
                        // no need for explicit initialization for non-pointer classes
                        out << " " << m.get_name() << ";" << endl;
                }
                out << endl; // new line after access level
        }

        // end class definition
        out << "};" << endl;
        out << endl;
        out << "#endif" << endl;

        return include_path;
}

void lang_cpp::write_source(string base_dir, class_def &c, string header_file) const
{
        string path = base_dir + c.get_name() + ".cpp";
        ofstream out;
        if (!open_file(path, out, "//")) {
                error("Could not open file: " + path);
        }
        
        // include this class's header
        out << "#include \"" + header_file + "\"" << endl;
        
        out << "using namespace std;" << endl;
        out << endl;

        for (constructor ctor : c.get_constructors()) {
                out << c.get_name() << "::";
                out << c.get_name();
                out << "(";
                print_parameters(out, &ctor);
                out << ")" << endl;
                out << "{" << endl;
                out << language::EIGHT_SPACES << "// TODO: implement" << endl;
                out << "}" << endl;
                out << endl;
        }
        if (c.has_explicit_destructor()) {
                out << c.get_name() << "::";
                out << "~" << c.get_name() << "()" << endl;
                out << "{" << endl;
                out << language::EIGHT_SPACES << "// TODO: implement" << endl;
                out << "}" << endl;
                out << endl;
        }
        for (method m : c.get_methods()) {
                out << types.convert(m.get_return_type()) << " ";
                out << c.get_name() << "::" << m.get_name();
                out << "(";
                print_parameters(out, &m);
                out << ")";
                out << endl;
                out << "{";
                out << endl;
                if (m.is_setter()) {
                    out << language::EIGHT_SPACES;
                    out << m.get_member()->get_name() << " = value;" << endl;
                }
                else if (m.is_getter()) {
                    out << language::EIGHT_SPACES << "return " << m.get_member()->get_name() << ";" << endl;
                }
                else {
                    out << language::EIGHT_SPACES << "// TODO: implement" << endl;
                }
                out << "}" << endl;
                out << endl;
        }
}


