#ifndef PARSER_H
#define PARSER_H
#include <vector>
#include <string>
#include "SyntaxToken.h"
#include "Lexer.h"
#include "AstNode.h"
#include "BinOpNode.h"
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

    public:
    Parser(std::string text);
    ASTNode* parseExpression(int minimumPrecedence);
    ASTNode* parseCompoundStatement();
    ASTNode* parseStatement();
    ASTNode* parseIfStatement();
    ASTNode* parsePrintStatement();
    ASTNode* parseVariableDeclarationStatement();
    void printTokens();

};
#endif