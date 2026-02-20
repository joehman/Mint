
#ifndef mtScope_h
#define mtScope_h

#include "mtHashmap.h"

// totally arbitrary
#define mtScopeDefaultSize 8

struct mtScope {
    struct mtScope* parent;    
    struct mtHashMap* variables; // Contains mtObjects

    struct mtHashMap* functions; // Contains mtFunctions
    struct mtHashMap* CFunctions; // Contains mtCFunctions
};

struct mtScope* mtCreateScope();
void mtDeleteScope(struct mtScope* scope);

struct mtObject* mtGetObjectFromScope(struct mtScope* scope, const char* key);
struct mtFunction* mtGetFunctionFromScope(struct mtScope* scope, const char* key);
struct mtCFunction* mtGetCFunctionFromScope(struct mtScope* scope, const char* key);

int mtAddCFunctionToScope(struct mtScope* scope, const char* key, struct mtCFunction* cFunc);
int mtAddFunctionToScope(struct mtScope* scope, const char* key, struct mtFunction* func);
int mtAddObjectToScope(struct mtScope* scope, const char* key, struct mtObject* func);

#endif
