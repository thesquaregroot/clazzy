#ifndef CLASS_DEF_H
#define CLASS_DEF_H

#include <vector>
#include <map>
#include <string>

class class_def {
    private:
        // stores functions (name to parameter list mapping)
        std::map<std::string, std::vector<std::string> > functions;
        // stores member variables (names)
        std::vector<std::string> members;
    
    public:
        // stores a class with a set of names parameters
        void add_function(const std::string&, std::vector<std::string>&);
        // stores a member variable name
        void add_member(const std::string&);
        // returns the map of function names to their parameters
        std::map<std::string, std::vector<std::string> > get_functions() const;
        // gets the members of this class
        std::vector<std::string> get_members() const;
};

#endif
