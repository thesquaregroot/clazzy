#ifndef CLASS_DEF_H
#define CLASS_DEF_H

#include <vector>
#include <map>
#include <string>

class class_def {
    private:
        std::string name;
        // stores functions (name to parameter list mapping)
        std::map<std::string, std::vector<std::string> > functions;
        // stores member variables (names)
        std::vector<std::string> members;
        // stores parent class names
        std::vector<std::string> parents;
    
    public:
        class_def() {};
        class_def(const std::string&);

        void set_name(const std::string&);
        std::string get_name() const;

        // stores a class with a set of names parameters
        void add_function(const std::string&, std::vector<std::string>&);
        // stores a member variable name
        void add_member(const std::string&);
        // stores a parent class/interface name
        void add_parent(const std::string&);
        // returns the map of function names to their parameters
        std::map<std::string, std::vector<std::string> > get_functions() const;
        // gets the members of this class
        std::vector<std::string> get_members() const;
        // gets the parents of this class
        std::vector<std::string> get_parents() const;
};

#endif
