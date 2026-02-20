// This module handles all input and output

#include <mtModule.h>
#include <stdio.h>

int a;

struct mtObject* print(struct mtObject* arg)
{
    if (!arg->type.str)
    {
        return NULL; 
    }
    
    char* str = arg->type.str(arg->data);
    if (!str)
        return NULL;

    printf("%s\n", str);

    free(str);
    return NULL;
}

struct mtCFunction functions[] = {
    { "print", &print },
    { NULL, NULL } // end of the array
};

struct mtModuleDef moduleDef = {
    "io",
    functions
};

struct mtModuleDef* mtModuleInitFunctionSymbol(void) 
{
    return &moduleDef;    
}
