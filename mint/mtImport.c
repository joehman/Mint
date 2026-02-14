#include "mtImport.h"

void interpretImport(struct ASTNode* node, struct mtScope* scope)
{
    if (node->type != NodeType_Import)
        return;

    struct ASTNode* identifierNode = node->children[0];

    char* identifierStr = malloc(identifierNode->token.size); 
    mtGetTokenString(identifierNode->token, identifierStr, identifierNode->token.size);

    struct mtModuleDef* moduledef = mtLoadModule(identifierStr);
    
    mtLoadModuleIntoScope(scope, moduledef);
}

