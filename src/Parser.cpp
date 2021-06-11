#include <iostream>
#include <vector>
#include "../headers/Parser.h"
#include "../headers/BinOpNode.h"
#include "../headers/IntNode.h"
#include "../headers/PrintNode.h"

#include "../headers/CompoundStatementNode.h"
#include "../headers/VariableDeclarationNode.h"
#include "../headers/BooleanLiteralNode.h"
#include "../headers/IfStatementNode.h"
#include "../headers/VariableNode.h"

Parser::Parser(std::string text) : lexer{text}{
    //Perform Lexical Analysis
    while (!lexer.hasReachedEOF()) {tokens.push_back(lexer.lex());} 
};

/**
 * Returns true if the passed Syntax Type is a binary operator
 */
bool Parser::isBinaryOperator(SyntaxType syntaxType){
    switch(syntaxType)
    {
        case MultToken:
        case DivideToken:
        case AddToken:
        case MinusToken:
        case LessThanToken:
        case GreaterThanToken:
        case LessThanOrEqualToToken:
        case GreaterThanOrEqualToToken:
        case LogicalOrToken:
        case LogicalAndToken:
            return true;
    }
    return false;
}

/**
 * Prints all of the tokens
 */ 
void Parser::printTokens(){
    std::cout << "Printing Tokens...\n";
    for (auto x : tokens)
    {
        std::cout << x.text << "\n";
    }
};

SyntaxToken Parser::peek(int offset){
    auto index = position + offset;
    return tokens[index];
};

SyntaxToken Parser::getCurrentToken(){
    return peek(0);
};

SyntaxToken Parser::getNextToken(){
    auto current = getCurrentToken();
    position++;
    return current;
};

SyntaxToken Parser::match(SyntaxType expected, std::string text){
    auto current = getCurrentToken();
    if (current.syntaxType == expected)
    {
        return getNextToken();
    }
    else
    {
        std::cerr << "Unexpected Token \"" << current.text << "\". Expected " << text << ".";
    }
    exit(EXIT_FAILURE);
};

int Parser::getOperatorPrecedence(SyntaxType op){
    switch (op)
    {
        case MultToken:
        case DivideToken:
            return 4;
        case AddToken:
        case MinusToken:
            return 3;
        case LessThanToken:
        case GreaterThanToken:
        case GreaterThanOrEqualToToken:
        case LessThanOrEqualToToken:
            return 3;
        case LogicalAndToken:
            return 2;
        case LogicalOrToken:
            return 1;
    }
    return 0;
}

OperatorType Parser::getOperatorType(SyntaxType op){
    switch(op)
    {
        case AddToken:
            return AdditionOperator;
        case MultToken:
            return MultiplicationOperator;
        case DivideToken:
            return DivisionOperator;
        case MinusToken:
            return SubtractionOperator;
        case GreaterThanToken:
            return GreaterThanOperator;
        case LessThanToken:
            return LessThanOperator;
        case LogicalAndToken:
            return LogicalAndOperator;
        case LogicalOrToken:
            return LogicalOrOperator;
        default:
            exit(EXIT_FAILURE);
    }
};

ASTNode* Parser::parsePrimary(){
    std::string result;
    ASTNode *tree;
    std::string identifier;
    auto localSymbolTable = symbolTableStack.top();
    switch(getCurrentToken().syntaxType)
    {
        case IntegerLiteralToken:
            result = match(IntegerLiteralToken, "Integer Literal").text;
            return new IntNode(std::stoi(result));
        case TrueKeywordToken:
            match(TrueKeywordToken, "true");
            return new BooleanLiteralNode(true);
        case FalseKeywordToken:
            match(FalseKeywordToken, "false");
            return new BooleanLiteralNode(false);
        case LeftParenthesisToken:
            match(LeftParenthesisToken, "(");
            tree = parseExpression(0);
            match(RightParenthesisToken, ")");
            return tree;
        case IdentifierToken:
            identifier = getCurrentToken().text;
            match(IdentifierToken, "identifier");
            return new VariableNode(localSymbolTable[identifier], identifier);
        default:
            match(IntegerLiteralToken, "Integer Literal");
            exit(EXIT_FAILURE);
    }
    return nullptr;
};

/**
 * Construct an AST via precendence climbing parsing
 */
ASTNode* Parser::parseExpression(int minimumPrecedence){
    ASTNode *left = parsePrimary(), *right;
    SyntaxType lookAhead = getCurrentToken().syntaxType;
    
    while (isBinaryOperator(lookAhead) && getOperatorPrecedence(lookAhead) > minimumPrecedence)
    {
        getNextToken();
        right = parseExpression(getOperatorPrecedence(lookAhead));
        left = new BinOpNode(left, getOperatorType(lookAhead), right);
        lookAhead = getCurrentToken().syntaxType;
        if (lookAhead == RightParenthesisToken || lookAhead == SemicolonToken)
        {
            return left;
        }
    }
    return left;
};

ASTNode* Parser::parseStatement(){
    switch(getCurrentToken().syntaxType)
    {
        case IfToken:
            return parseIfStatement();
        case LeftCurlyBraceToken:
            return parseCompoundStatement();
        case PrintToken:
            return parsePrintStatement();
        case VarKeywordToken:
        case IntKeywordToken:
        case BoolKeywordToken:
            return parseVariableDeclarationStatement();
    }
    
    return nullptr;
}

ASTNode* Parser::parseCompoundStatement(){
    match(LeftCurlyBraceToken, "{");
    scope++;
    symbolTableStack.push(std::unordered_map<std::string, Type>());
    std::cout << "Scope: " << scope << "\n";
    std::vector<ASTNode*> statements;
    /*While inside the compound staement*/
    while (getCurrentToken().syntaxType != RightCurlyBraceToken)
    {  
        /*Add each statement to the statement list*/
        statements.push_back(parseStatement());
    }
    match(RightCurlyBraceToken, "}");
    scope--;
    symbolTableStack.pop();
    return new CompoundStatementNode(statements);
}

ASTNode *Parser::parseIfStatement(){
    ASTNode *condition, *stmtBody, *elseBody = nullptr;
    match(IfToken, "if");
    match(LeftParenthesisToken, "(");
    condition = parseExpression(0);
    match(RightParenthesisToken, ")");
    stmtBody = parseStatement();
    if (getCurrentToken().syntaxType == ElseToken)
    {
        match(ElseToken, "else");
        elseBody = parseStatement();
    }

    return new IfStatementNode(condition, stmtBody, elseBody);
}

ASTNode* Parser::parsePrintStatement(){
    ASTNode *contents = nullptr;
    match(PrintToken, "print");
    match(LeftParenthesisToken, "(");
    contents = parseExpression(0);
    match(RightParenthesisToken, ")");
    match(SemicolonToken, ";");
    return new PrintNode(contents);
}

ASTNode* Parser::parseVariableDeclarationStatement(){
    ASTNode *rhs = nullptr;
    auto localSymbolTable = symbolTableStack.top();
    symbolTableStack.pop();
    std::string identifier;
    SyntaxToken token = getCurrentToken();
    bool isVarType = false;
    Type t;
    switch(getCurrentToken().syntaxType)
    {
        case IntKeywordToken:
            match(IntKeywordToken, "int");
            t = IntegerPrimitive;
            break;
        case DoubleKeywordToken:
            match(DoubleKeywordToken, "double");
            break;
        default:
            t = ImplicitVarType;
            match(VarKeywordToken, "var");
            isVarType = true;
            break;
    }
    if (token.syntaxType == IdentifierToken){
        identifier = token.text;
    }

    localSymbolTable[identifier] = t;
    symbolTableStack.push(localSymbolTable);

    match(IdentifierToken, "an identifier");
    token = getCurrentToken();
    //Implicitly typed variables require an assignment so as to deduce the type
    if (isVarType)
    {
        match(EqualsToken, "=");
        rhs = parseExpression(0);
        match(SemicolonToken, ";");
    }
    else
    {
        if (token.syntaxType != EqualsToken)
        {
            match(SemicolonToken, ";");
        }
        else
        {
            match(EqualsToken, "=");
            rhs = parseExpression(0);
            match(SemicolonToken, ";");
        }
    }
    return new VariableDeclarationNode(new VariableNode(t, identifier), rhs);
}
