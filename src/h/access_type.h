#ifndef __CRANBERRY_ACCESS_TYPE_H__
#define __CRANBERRY_ACCESS_TYPE_H__

namespace cranberry {
    enum access_type {
        VISIBLE_ACCESS, // public
        HIDDEN_ACCESS, // private
        CHILD_VISIBLE_ACCESS, // protected
        ASSEMBLY_VISIBLE_ACCESS // package
    };
}

#endif
