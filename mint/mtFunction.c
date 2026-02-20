
#include "mtFunction.h"
#include <stdarg.h>

#include "mtBlock.h"
#include "mtExpression.h"
#include "mtUtilities.h"

static void interpreterError(struct ASTNode* node, const char* fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    fprintf(stderr, "Error while interpreting on line %d: \n\t", 
            node->token.line 
    );
    vfprintf(stderr, fmt, args);

    if (fmt[strlen(fmt)] != '\n')
    {
        printf("\n");
    }
}

int interpretCFunctionCall(struct mtCFunction* func, struct ASTNode* node, struct mtScope* scope)
{
    // TODO : Make it possible to pass more than one argument to a CFunction

    struct ASTNode* argumentList = node->children[1];
    struct mtObject* argument = NULL; 
   
    if (argumentList->childCount > 0)
    {
        argument = interpretExpression(argumentList->children[0], scope);
    }

    if (!argument)
    {
        interpreterError(argumentList->children[0], "Failed to interpret node as expression");
        return mtFail;
    }

    func->func(argument);

    return mtSuccess; 
}

int interpretMintFunctionCall(struct mtFunction* func, struct ASTNode* node, struct mtScope* scope)
{
    struct ASTNode* identifierNode = node->children[0];
    struct ASTNode* argumentList = node->children[1];

    char* identifierStr = malloc(identifierNode->token.size);
    mtGetTokenString(identifierNode->token, identifierStr, identifierNode->token.size);

    if (argumentList->childCount != func->parameterCount)   
    {
        if (argumentList->childCount > func->parameterCount)
        {
            interpreterError(node, 
                             "Too many arguments to function \"%s\", expected %d arguments!", 
                             identifierStr, func->parameterCount);
            return mtFail;
        }
        if (argumentList->childCount < func->parameterCount)
        {
            interpreterError(node, 
                             "Too few arguments to function \"%s\", expected %d arguments!", 
                             identifierStr, func->parameterCount);
            return mtFail;
        }
    }

    struct mtScope* arguments = mtCreateScope();
    arguments->parent = scope; 

    for (size_t i = 0; i < argumentList->childCount; i++)
    {
        struct mtObject* argument = interpretExpression(argumentList->children[i], scope);

        if (!argument)
            return mtFail;
        mtAddObjectToScope(arguments, func->parameters[i].identifier, argument); 
    }
   
    interpretBlock(func->block, arguments);

    return mtSuccess;
}

struct mtObject* interpretFunctionCall(struct ASTNode* node, struct mtScope* scope, bool* wasFunc)
{
    *wasFunc = false; 
    if (node->type != (NodeType_FunctionCall))
    {
        return NULL;
    }
    *wasFunc = true;

    struct Token identifier = node->children[0]->token; 
    struct ASTNode* argumentList = node->children[1];

    char tokenStr[identifier.size];
    mtGetTokenString(identifier, (char*)&tokenStr, identifier.size);
    
    struct mtFunction* func = mtGetFunctionFromScope(scope, tokenStr);
    struct mtCFunction* cFunc = mtGetCFunctionFromScope(scope, tokenStr);

    bool foundFunc = false;
    if (func)
    {
        foundFunc = true; 
        interpretMintFunctionCall(func, node, scope);
    } 
    else if (cFunc)
    {
        foundFunc = true;
        interpretCFunctionCall(cFunc, node, scope);  
    }
    
    return NULL;
}

void interpretFunctionDef(struct ASTNode* node, struct mtScope* scope)
{
    // children of the function_def node:
    // 1st      child: identifier
    // 2nd      child: parameterList 
    // 3rd      child: block
    //
    // children of the parameterList node:
    // 1...nth  child: parameter
    if (node->type != NodeType_FunctionDefinition)
    {
        return;
    }

    struct mtFunction* out = malloc(sizeof(struct mtFunction));

    struct Token identifier = node->children[0]->token;
    if (identifier.type != TokenType_Identifier)
    {
        return;
    }
    char tokenStr[identifier.size];
    mtGetTokenString(identifier, (char*)&tokenStr, identifier.size);
    out->identifier = strndup(tokenStr, identifier.size);
    
    struct ASTNode* parameterList = node->children[1];

    out->parameterCount = parameterList->childCount;
    out->parameters = malloc(sizeof(struct Parameter) * out->parameterCount);
    
    for (size_t i = 0; i < out->parameterCount; i++)
    {
        struct ASTNode* parameterNode = parameterList->children[i];         
       
        size_t tokenSize = parameterNode->token.size;
        char tokenStr[parameterNode->token.size];

        mtGetTokenString(parameterNode->token, (char*) &tokenStr, tokenSize);
        out->parameters[i].identifier = strndup(tokenStr, tokenSize); 
        out->parameters[i].type = NULL;
    }
    struct ASTNode* block = node->children[2];
    out->block = block;

    mtAddFunctionToScope(scope, out->identifier, out);
}
