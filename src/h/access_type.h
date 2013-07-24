#ifndef ACCESS_TYPE_H
#define ACCESS_TYPE_H

namespace cranberry {
    enum access_type {
        VISIBLE, // public
        HIDDEN, // private
        CHILD_VISIBLE, // protected
        ASSEMBLY_VISIBLE // package
    };
}

#endif
