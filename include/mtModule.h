#ifndef mtModule_h
#define mtModule_h

#include <stdlib.h>

#include <mtCFunction.h>
#include <mtObject.h>

#define mtInitFunctionSymbolName moduleInit

struct mtModuleDef 
{
    const char* name;
    struct mtCFunction* functions;
};

typedef struct mtModuleDef* (*mtModuleInitFunction)(void);

#endif
