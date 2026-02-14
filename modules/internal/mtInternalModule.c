
#include "mtModule.h"
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <mtUtilities.h>

#define mtUnix __unix__

#ifdef mtUnix 
#include <dlfcn.h>
#endif

#include <internal/mtInternalModule.h>

void moduleError(char* fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    fprintf(stderr, "ModuleError: \n\t");
    vfprintf(stderr, fmt, args);
    fprintf(stderr, "\n");
}


struct mtModuleDef* mtLoadModule(const char* name)
{
#ifdef mtUnix
    char namepath[128];
    memset(&namepath, 0, mtArraySize(namepath));
    
    sprintf((char*)&namepath, "./lib%s.so", name);

    void* ptr = dlopen(namepath, RTLD_LAZY);

    if (!ptr)
    {
        const char* error = dlerror(); 
        moduleError("%s", error); 

        return NULL;
    }

    mtModuleInitFunction init = dlsym(ptr, mtModuleInitFunctionSymbolString); 

    struct mtModuleDef* def = init();

    return def; 
#endif
    moduleError("mtLoadModule not implemented on this platform!");
    return NULL;
}

void mtLoadModuleIntoScope(struct mtScope* scope, struct mtModuleDef* module)
{
    struct mtCFunction* CFunction = &module->functions[0];
    
    for (int i = 1; CFunction->func; i++)
    {
        mtHashMapPut(scope->CFunctions, CFunction->identifier, CFunction);
        CFunction = &module->functions[i];
    }
}

