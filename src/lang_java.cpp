
#include "h/lang_java.h"
#include "h/io_functions.h"
#include "h/string_functions.h"
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
        // container types
        //types.add_type("array", "");
        types.add_type("deque", "Deque", new string("java.util.Deque"));
        types.add_type("list", "List", new string("java.util.List"));
        types.add_type("set", "Set", new string("java.util.Set"));
        types.add_type("stack", "Stack", new string("java.util.Stack"));
        types.add_type("queue", "Queue", new string("java.util.Queue"));
        types.add_type("map", "Map", new string("java.util.Map"));
        //types.add_type("pointer", "");
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
        // generate source files
        for (class_def c : classes) {
                for (design_pattern dp : c.get_design_patterns()) {
                        if (dp == SINGLETON) {
                                // create member
                                member mem(type_hint(c.get_name()), "instance");
                                mem.set_getter(true, "getInstance");
                                mem.set_static(true);
                                mem.set_initialized(true);
                                c.add_member(mem);
                                // create private constructor
                                constructor ctor;
                                ctor.set_visibility(HIDDEN_ACCESS);
                                c.add_constructor(ctor);
                        }
                }
                
                ofstream out;
                open_file(dir + to_full_camel_case(c.get_name()) + ".java", out, "//");
                // declare package
                out << "package " << package << ";" << endl;
                out << endl;
                // imports
                vector<string> imports = types.get_imports(c.get_referenced_types());
                for (string import : imports) {
                        out << "import " << import << ";" << endl;
                }
                if (imports.size() > 0) {
                        out << endl;
                }
                // define class
                out << "public class " << to_full_camel_case(c.get_name());
                for (type_hint parent : c.get_parents()) {
                        out << " extends " << types.convert_cc(parent);
                }
                out << " {" << endl;
                // members
                for (member m : c.get_members()) {
                        out << language::FOUR_SPACES;
                        // visibility (prefixes include following whitespace)
                        out << access_prefixes[m.get_visibility()];
                        // modifiers
                        if (m.is_static()) {
                                out << "static ";
                        }
                        // definition
                        out << types.convert_cc(m.get_type()) << " ";
                        out << to_camel_case(m.get_name());
                        if (m.is_initialized()) {
                                out << " = new " << types.convert_cc(m.get_type()) << "();" << endl;
                        } else {
                                out << ";" << endl;
                        }
                }
                // extra newline between members and constructors
                if (c.get_members().size() > 0 && (c.get_constructors().size() > 0 || c.get_methods().size() > 0)) {
                        out << language::FOUR_SPACES << endl;
                }
                for (constructor ctor : c.get_constructors()) {
                        out << language::FOUR_SPACES;
                        // use normal sort of constructor
                        out << access_prefixes[ctor.get_visibility()];
                        out << to_full_camel_case(c.get_name());
                        out << "(";
                        map<string,type_hint> params = ctor.get_parameters();
                        auto it = params.cbegin();
                        while (it != params.end()) {
                                out << types.convert_cc(it->second) << " ";
                                out << it->first;
                                if (++it != params.cend()) {
                                        out << ", ";
                                }
                        }
                        out << ")" << endl;
                        // body shell
                        out << language::FOUR_SPACES << "{" << endl;
                        out << language::EIGHT_SPACES << "// TODO: implement" << endl;
                        out << language::FOUR_SPACES << "}" << endl;
                        out << endl;
                }
                if (c.has_explicit_destructor()) {
                        out << language::FOUR_SPACES;
                        // destructors in Java (finalize) must be protected
                        out << "protected finalize() throws Throwable" << endl;
                        out << language::FOUR_SPACES << "{" << endl;
                        out << language::EIGHT_SPACES << "// TODO: implement" << endl;
                        out << language::FOUR_SPACES << "}" << endl;
                        out << endl;
                }
                // methods
                for (method m : c.get_methods()) {
                        out << language::FOUR_SPACES;
                        // visibility (prefixes include following whitespace)
                        out << access_prefixes[m.get_visibility()];
                        // modifiers
                        if (m.is_static()) {
                                out << "static ";
                        }
                        if (m.is_read_only()) {
                                warn("In class " + to_full_camel_case(c.get_name()) + ": the method " + to_camel_case(m.get_name()) + " cannot be declared read-only as Java does not support this feature.");
                        }
                        // definition
                        out << types.convert_cc(m.get_return_type()) << " ";
                        out << to_camel_case(m.get_name());
                        out << "(";
                        map<string,type_hint> params = m.get_parameters();
                        auto it = params.cbegin();
                        while (it != params.end()) {
                                out << types.convert_cc(it->second) << " ";
                                out << it->first;
                                if (++it != params.cend()) {
                                        out << ", ";
                                }
                        }
                        out << ")" << endl;
                        // body shell
                        out << language::FOUR_SPACES << "{" << endl;
                        if (m.is_getter()) {
                                out << language::EIGHT_SPACES << "return " << m.get_member()->get_name() << ";" << endl;
                        } else if (m.is_setter()) {
                                out << language::EIGHT_SPACES << m.get_member()->get_name() << " = value;" << endl;
                        } else {
                                out << language::EIGHT_SPACES << "// TODO: implement" << endl;
                        }
                        out << language::FOUR_SPACES << "}" << endl;
                        out << endl;
                }
                out << "}" << endl;
        }
}

