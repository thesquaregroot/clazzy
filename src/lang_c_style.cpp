
#include "h/lang_c_style.h"
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

void lang_c_style::create(
                        const vector<class_def> &classes,
                        const map<string,string> &properties
        ) const
{
        for (class_def c : classes) {
                for (design_pattern dp : c.get_design_patterns()) {
                        if (dp == SINGLETON) {
                                // create member
                                member mem(type_hint(c.get_name()), "_instance");
                                mem.set_getter(true, "get_instance");
                                mem.set_static(true);
                                mem.set_initialized(true);
                                c.add_member(mem);
                                // create private constructor
                                constructor ctor;
                                ctor.set_visibility(HIDDEN_ACCESS);
                                c.add_constructor(ctor);
                        }
                }
                // create file
                debug("Creating code for class: " + c.get_name());
                string base_dir = "./clazzy_" + get_simple_name() + "/";
                if (!chk_mkdir(base_dir)) {
                        error("Could not create directory: " + base_dir);
                }
                string header_name = write_header(base_dir, c);
                write_source(base_dir, c, header_name);
        }
}

void lang_c_style::print_parameters(ofstream &out, parameterized* const p) const
{
        map<string,type_hint> params = p->get_parameters();
        for (auto param_it = params.cbegin(); param_it != params.cend(); param_it++) {
                // TODO: parameter modifiers
                // map string -> type_hint
                out << types.convert(param_it->second) << " " << param_it->first;
                if (param_it != --params.cend()) {
                        out << ", ";
                }
        }
}

