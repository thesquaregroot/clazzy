#ifndef __CRANBERRY_ACCESS_TYPE_H__
#define __CRANBERRY_ACCESS_TYPE_H__

namespace cranberry {
    enum access_type {
        VISIBLE, // public
        HIDDEN, // private
        CHILD_VISIBLE, // protected
        ASSEMBLY_VISIBLE // package
    };
}

#endif
