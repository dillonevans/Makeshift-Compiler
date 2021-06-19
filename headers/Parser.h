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
    SyntaxToken peek(int offset);
    SyntaxToken getCurrentToken();
    SyntaxToken getNextToken();
    SyntaxToken match(SyntaxType expected, std::string text);
    ASTNode* parsePrimary();

    OperatorType getOperatorType(SyntaxType op);
    bool isBinaryOperator(SyntaxType syntaxType);
    int getOperatorPrecedence(SyntaxType op);
    int position = 0;
    int scope = 0;
    std::stack<ScopeTreeNode*> scopeTreeStack;

public:
    Parser(std::string text);
    ASTNode* parseExpression(int minimumPrecedence);
    ASTNode* parseCompoundStatement();
    ASTNode* parseStatement();
    ASTNode* parseIfStatement();
    ASTNode* parsePrintStatement();
    ASTNode* parseVariableDeclarationStatement();
    ASTNode* parseReturnStatement();
    ASTNode* parseFunctionDeclaration();
    ASTNode* parseProgram();
    ASTNode* parseExpressionStatement();
    ASTNode* parseWhileStatement();

    void printTokens();
};
#endif