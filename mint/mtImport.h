#ifndef mtImport_h
#define mtImport_h

#include <mtAST.h>
#include <mtInternalModule.h>

void interpretImport(struct ASTNode* node, struct mtScope* scope);

#endif
