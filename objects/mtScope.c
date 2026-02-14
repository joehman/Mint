#include "mtScope.h"

struct mtScope* mtCreateScope()
{
    struct mtScope* scope = malloc(sizeof(struct mtScope));

    scope->parent = NULL;
    scope->variables = mtHashMapCreate(mtScopeDefaultSize);
    scope->functions = mtHashMapCreate(mtScopeDefaultSize);
    scope->CFunctions = mtHashMapCreate(mtScopeDefaultSize);

    return scope;
}

struct mtObject* getObjectFromScope(struct mtScope* scope, const char* key)
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

struct mtFunction* getFunctionFromScope(struct mtScope* scope, const char* key)
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

struct mtCFunction* getCFunctionFromScope(struct mtScope* scope, const char* key)
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
