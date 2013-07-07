#ifndef LANGUAGE_H
#define LANGUAGE_H

#include <vector>
#include <string>

class class_def;

class language {
    private:
        static const char *name;

    public:
        virtual ~language();

        virtual std::string get_name() const = 0;
        virtual void create(const std::vector<class_def>&) const = 0;
};

#endif
