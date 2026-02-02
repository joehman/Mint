#include "internal/mtAST.h"


struct ASTNode* mtASTAddNode(struct ASTNode* parent)
{
    if (parent->childCount >= parent->childCapacity)
    {
        parent->childCapacity *= 2;
        parent->children = realloc(parent->children, sizeof(struct ASTNode*) * parent->childCapacity);
    }

    int index = parent->childCount;
    struct ASTNode* ptr = ( parent->children[index] = mtASTCreateNode() );
    parent->childCount++;

    return ptr;
}   

int mtASTAddChildNode(struct ASTNode* parent, struct ASTNode* child)
{
    if (parent->childCount >= parent->childCapacity)
    {
        parent->childCapacity *= 2;
        parent->children = realloc(parent->children, sizeof(struct ASTNode*) * parent->childCapacity);
    }
    int index = parent->childCount;
    
    parent->children[index] = child;
    parent->childCount++;

    return index;
}   
struct ASTNode* mtASTCreateNode()
{
    struct ASTNode* out = malloc( sizeof(struct ASTNode) );
    out->type = NodeType_None;
    out->childCount = 0;
    out->childCapacity = mtASTInitialChildCapacity;

    out->children = malloc (sizeof(struct ASTNode*) * mtASTInitialChildCapacity);
    mtCreateToken(&out->token);

    return out;
}
struct ASTNode* mtASTTokenCreateNode(struct Token token)
{
    struct ASTNode* out = malloc( sizeof(struct ASTNode) );
    
    out->childCount = 0;
    out->childCapacity = mtASTInitialChildCapacity;
    
    out->children = malloc (sizeof(struct ASTNode*) * mtASTInitialChildCapacity);
    out->token = token;

    return out;
}

void mtASTFree(struct ASTNode* node)
{
    if (node == NULL) return;

    // have to free the struct but also the rootNode->children array.
    for (size_t i = 0; i < node->childCount; i++)
    {
        //call recursively
        mtASTFree(node->children[i]);
    }
    free(node->children);
    free(node);
}

void printASTTreeRecurse(struct ASTNode* node, int depth)
{
    for (size_t i = 0; i < depth; i++) {
        printf("|\t"); 
    } 
    mtPrintASTNode(node);
    printf("\n");

    for (size_t i = 0; i < node->childCount; i++) 
    {
        if (!node->children[i])
        {
            // print null with the proper depth
            for (size_t i = 0; i < depth; i++) {
                printf("|\t"); 
            } 
            printf("(null)\n");
            continue;
        }
        printASTTreeRecurse(node->children[i], depth+1);  
    }

}

void mtPrintASTTree(struct ASTNode* node)
{
    int depth = 0;
    printASTTreeRecurse(node, depth);    
}

void mtPrintASTNode(struct ASTNode* node)
{
    char buf[128];
    memset(&buf, 0, 128);

    strncpy((char*)&buf, node->token.string, node->token.size);

    printf("tok: %s type: ", buf);
    mtPrintASTNodeType(node);
}

void mtPrintASTNodeType(struct ASTNode* node)
{
    int type = node->type;
    
    #define check(nodetype, conststr) case nodetype: printf(conststr); break;

    switch (type)
    {
        check(NodeType_None, "None")

        check(NodeType_Assignment, "Assign")
        check(NodeType_BinaryOperator, "BinOp")
        check(NodeType_Number, "Number")
        check(NodeType_Identifier, "Identifier")
        check(NodeType_Block, "Block")

        check(NodeType_GreaterThan, "GreaterThan")
        check(NodeType_LesserThan, "LesserThan")
        check(NodeType_GreaterThanOrEqual, "GreaterOrEqual")
        check(NodeType_LesserThanOrEqual, "LesserOrEqual")

        check(NodeType_IsEqual, "IsEqual")
        check(NodeType_IsNotEqual, "IsNotEqual")

        check(NodeType_IfStatement, "IfStatement")
        check(NodeType_FunctionDefinition, "Function")
        check(NodeType_FunctionCall, "FunctionCall")
        check(NodeType_ParameterList, "Params")
        check(NodeType_ArgumentList, "Args")
    }
}
