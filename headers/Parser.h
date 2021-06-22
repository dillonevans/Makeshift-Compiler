#ifndef PARSER_H
#define PARSER_H
#include <vector>
#include <string>
#include "SyntaxToken.h"
#include "Lexer.h"
#include "AstNode.h"
#include "BinOpNode.h"
#include <unordered_map>
#include <stack>
#include <string>
#include "ScopeTreeNode.h"
#include "FunctionNode.h"
#include "Value.h"
class Parser
{
private:
    std::vector<SyntaxToken> tokens;
    Lexer lexer;
    int scope = 0;
    int position = 0;
    int localOffset = 0;
    int getOperatorPrecedence(SyntaxType op);
    bool isBinaryOperator(SyntaxType syntaxType);
    std::stack<ScopeTreeNode*> scopeTreeStack;

    SyntaxToken peek(int offset);
    SyntaxToken getCurrentToken();
    SyntaxToken getNextToken();
    SyntaxToken match(SyntaxType expected, std::string text);
    OperatorType getOperatorType(SyntaxType op);

    ASTNode* parsePrimary();
    ASTNode* parseExpression(int minimumPrecedence);
    ASTNode* parseCompoundStatement();
    ASTNode* parseStatement();
    ASTNode* parseIfStatement();
    ASTNode* parsePrintStatement();
    ASTNode* parseVariableDeclarationStatement();
    ASTNode* parseReturnStatement();
    ASTNode* parseFunctionDeclaration();
    ASTNode* parseExpressionStatement();
    ASTNode* parseWhileStatement();
    ASTNode* parseAssignmentStatement();
    ASTNode* resolve(std::string identifier, ScopeTreeNode* node);
    bool isRightAssociative(SyntaxType op);
public:
    Parser(std::string text);
    ASTNode* parseProgram();
    void printTokens();
};
#endif