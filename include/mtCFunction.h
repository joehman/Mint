
#ifndef mtCFunction_h
#define mtCFunction_h

struct mtCFunction {
    const char* identifier;

    // function pointer that returns mtObject
    struct mtObject* (*func)(struct mtObject*);
};

#endif 
