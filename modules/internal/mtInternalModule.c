
#include <stdio.h>
#include <stdarg.h>

#define mtUnix __unix__

#ifdef mtUnix 
#include <dlfcn.h>
#endif

#include <mtInternalModule.h>

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
    void* ptr = dlopen(name, RTLD_LAZY);

    if (!ptr)
    {
        char* error = dlerror(); 
        moduleError("%s", error); 
    }

    return ptr; 
#endif
    moduleError("mtLoadModule not implemented on this platform!");
    return NULL;
}

void mtLoadModuleIntoScope(struct mtScope* scope, struct mtModuleDef* module)
{
    struct mtCFunction* CFunction = &module->functions[0];

    while (CFunction->func)
    {
        mtHashMapPut(scope->CFunctions, CFunction->identifier, CFunction->func);
    }
}

