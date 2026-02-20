#include "mtScope.h"
#include "mtObject.h"
#include <mtUtilities.h>

struct mtScope* mtCreateScope()
{
    struct mtScope* scope = malloc(sizeof(struct mtScope));

    scope->parent = NULL;
    scope->variables = mtHashMapCreate(mtScopeDefaultSize);
    scope->functions = mtHashMapCreate(mtScopeDefaultSize);
    scope->CFunctions = mtHashMapCreate(mtScopeDefaultSize);

    return scope;
}

struct mtObject* mtGetObjectFromScope(struct mtScope* scope, const char* key)
{
    if (!scope)
    {
        return NULL;
    }

    struct mtObject* out = NULL;

    if ( (out = mtHashMapGet(scope->variables, key)) )
    {
        return out;
    }
    
    struct mtScope* currentScope = scope;
    while(currentScope)
    {
        if ( (out = mtHashMapGet(currentScope->variables, key)) )
        {
            return out;
        }
        
        // check the scope above
        currentScope = currentScope->parent;
    }

    return NULL;
}

struct mtFunction* mtGetFunctionFromScope(struct mtScope* scope, const char* key)
{
    if (scope == NULL)
    {
        return NULL;
    }
    
    struct mtFunction* out = NULL;
    
    struct mtScope* currentScope = scope;
    while (currentScope)
    {
        if ( (out = mtHashMapGet(currentScope->functions, key)) )
        {
            return out;
        }

        //check the scope above
        currentScope = currentScope->parent;
    }

    return NULL;
}

struct mtCFunction* mtGetCFunctionFromScope(struct mtScope* scope, const char* key)
{
    if (!scope)
    {
        return NULL;
    }

    struct mtCFunction* out = NULL;

    struct mtScope* currentScope = scope;
    while (currentScope)
    {
        if ( (out = mtHashMapGet(currentScope->CFunctions, key)) )
        {
            return out;
        }

        currentScope = currentScope->parent;
    }

    return NULL;
}

int mtAddCFunctionToScope(struct mtScope* scope, const char* key, struct mtCFunction* cFunc)
{
    mtHashMapPut(scope->CFunctions, key, cFunc); 
    return mtSuccess; 
}

int mtAddFunctionToScope(struct mtScope* scope, const char* key, struct mtFunction* func)
{
    mtHashMapPut(scope->functions, key, func); 
    return mtSuccess; 
}

int mtAddObjectToScope(struct mtScope* scope, const char* key, struct mtObject* object)
{
    mtHashMapPut(scope->variables, key, object); 
    return mtSuccess; 
}

void mtDeleteScope(struct mtScope* scope)
{
    mtHashMapDestroy(scope->variables, (void*)mtDeleteObject);
    mtHashMapDestroy(scope->functions, NULL);
    mtHashMapDestroy(scope->CFunctions, NULL);

    scope->parent = NULL;
    free(scope);
}
