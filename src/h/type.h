#ifndef TYPE_H
#define TYPE_H

namespace cranberry {
    enum type : unsigned short {
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
