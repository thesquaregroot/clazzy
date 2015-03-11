
#include "../libclazzy/io_helpers.h"
#include <vector>
using namespace clazzy;
using namespace std;

int main() {
    vector<Class> classes;
    // create class
    Class c("Blob");
    c.set_final(true);
    // with method
    Method m("jiggle");
    c.add_method(m);
    // add to list
    classes.push_back(c);
    // save
    return write(classes, "test.clz");
}

