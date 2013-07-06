#ifndef CLASS_DEF_H
#define CLASS_DEF_H

#include <vector>
#include <map>
#include <string>

class class_def {
    private:
        std::map<std::string, std::vector<std::string> > functions;
        std::vector<std::string> members;
    
    public:
        void add(std::string name, std::vector<std::string> params);
        void add(std::string name);
        std::map<std::string, std::vector<std::string> > get_functions() const;
        std::vector<std::string> get_members() const;
};

#endif
