#ifndef mtModule_h
#define mtModule_h

#include <stdlib.h>

#include <mtCFunction.h>
#include <mtObject.h>

#define mtModuleInitFunctionSymbol moduleInit

#define mtModuleStringify(x) #x
#define mtModuleToString(x) mtModuleStringify(x)

#define mtModuleInitFunctionSymbolString mtModuleToString(mtModuleInitFunctionSymbol)

struct mtModuleDef 
{
    const char* name;
    struct mtCFunction* functions;
};

typedef struct mtModuleDef* (*mtModuleInitFunction)(void);

#endif
