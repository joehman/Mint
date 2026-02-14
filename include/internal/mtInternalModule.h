#ifndef mtInternalModule_h
#define mtInternalModule_h

#include <mtModule.h>
#include <mtScope.h>

struct mtModuleDef* mtLoadModule(const char* name);

void mtLoadModuleIntoScope(struct mtScope* scope, struct mtModuleDef* module);

#endif
