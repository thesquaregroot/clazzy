#ifndef __CRANBERRY_TYPE_H__
#define __CRANBERRY_TYPE_H__

namespace cranberry {
    enum type {
        // generic types
        ARRAY,
        DEQUE,
        LIST,
        SET,
        STACK,
        QUEUE,
        MAP,
        POINTER,
        // "primitive" types
        BYTE,
        SHORT,
        INTEGER,
        LONG,
        CHARACTER,
        STRING,
        FLOAT,
        DOUBLE,
        BOOLEAN,
        VOID
    };
}

#endif
