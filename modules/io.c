// This module handles all input and output

#include <mtModule.h>
#include <stdio.h>

struct mtObject* print(struct mtObject* arg)
{
    if (!arg->type.str)
    {
        return NULL; 
    }

    printf("%s\n", arg->type.str(arg->data));
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

struct mtModuleDef* mtInitFunctionSymbolName(void) 
{
    return &moduleDef;    
}
