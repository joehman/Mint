
#ifndef mtCFunction_h
#define mtCFunction_h

struct mtCFunction {
    const char* identifier;
    struct mtObject* (*func)(struct mtObject*);
};

#endif 
