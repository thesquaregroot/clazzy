#ifndef LANGUAGE_H
#define LANGUAGE_H

#include <vector>
#include <string>
#include "class_def.h"

class language {
    private:
        static const std::string name;

    public:
        virtual std::string get_name() const = 0;
        virtual void create(const std::vector<class_def>&) const = 0;
};

#endif
