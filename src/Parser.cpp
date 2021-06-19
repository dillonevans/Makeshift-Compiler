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
#include "../headers/ScopeTreeNode.h"
#include "../headers/ReturnNode.h"
#include "../headers/TypeCheckingVisitor.h"
#include "../headers/FunctionNode.h"
#include "../headers/FunctionCallNode.h"
#include "../headers/WhileNode.h"

#include "../headers/ProgramNode.h"

/**
 * Constructor
 */
Parser::Parser(std::string text) : lexer{ text }
{
    //Perform Lexical Analysis
    while (!lexer.hasReachedEOF())
    {
        tokens.push_back(lexer.lex());
    }

    ///Push the Global Scope Symbol Table
    scopeTreeStack.push(new ScopeTreeNode());
};

/**
 * Returns true if the identifier is contained within the current or
 * parent scope.
 */
bool contains(ScopeTreeNode* node, std::string identifer)
{
    /*If there is no node, we've exhausted our search: return false*/
    if (!node)
    {
        return false;
    }

    /**
     * If the identifier is not found within the current scope,
     * recursively search the parent scope.
     */
    if (node->getSymbolTable().find(identifer) == node->getSymbolTable().end())
    {
        return contains(node->getParentNode(), identifer);
    }
    else
    {
        return true;
    }
}

/**
 * Returns true if the passed Syntax Type is a binary operator
 */
bool Parser::isBinaryOperator(SyntaxType syntaxType)
{
    switch (syntaxType)
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
        case EqualsToken:
        case AssignmentToken:
            return true;
    }
    return false;
}

/**
 * Prints all of the tokens
 */
void Parser::printTokens()
{
    std::cout << "Printing Tokens...\n";
    for (auto& x : tokens)
    {
        std::cout << x.getText() << "\n";
    }
};

/**
 * Looks ahead in the token table by an offset
 */
SyntaxToken Parser::peek(int offset)
{
    auto index = position + offset;
    return tokens[index];
};

/**
 * Return the current token
 */
SyntaxToken Parser::getCurrentToken()
{
    return peek(0);
};

/**
 * Consume and return the current token
 */
SyntaxToken Parser::getNextToken()
{
    auto current = getCurrentToken();
    position++;
    return current;
};

/**
 * Returns the current token if the passed syntax is what is expected
 */
SyntaxToken Parser::match(SyntaxType expected, std::string text)
{
    auto current = getCurrentToken();
    if (current.getSyntaxType() == expected)
    {
        return getNextToken();
    }
    else
    {
        std::cerr << "Unexpected Token \"" << current.getText() << "\". Expected " << text << ".";
    }
    exit(EXIT_FAILURE);
};

int Parser::getOperatorPrecedence(SyntaxType op)
{
    switch (op)
    {
        case AssignmentToken:
            return 6;
        case EqualsToken:
            return 5;
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

OperatorType Parser::getOperatorType(SyntaxType op)
{
    switch (op)
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
        case EqualsToken:
            return AssignmentOperator;
        default:
            exit(EXIT_FAILURE);
    }
};

/**
 * Parses tokens such as literals and function calls.
 */
ASTNode* Parser::parsePrimary()
{
    std::string result;
    ASTNode* tree;
    std::string identifier;
    switch (getCurrentToken().getSyntaxType())
    {
        case IntegerLiteralToken:
            result = match(IntegerLiteralToken, "Integer Literal").getText();
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
            identifier = getCurrentToken().getText();
            match(IdentifierToken, "identifier");

            //Add support for discerning function calls and variable names
            if (contains(scopeTreeStack.top(), identifier))
            {
                if (getCurrentToken().getSyntaxType() == LeftParenthesisToken)
                {
                    match(LeftParenthesisToken, "(");
                    match(RightParenthesisToken, ")");
                    return new FunctionCallNode(identifier);
                }
                return new VariableNode(scopeTreeStack.top()->getSymbolTable()[identifier], identifier);
            }
            else
            {
                std::cerr << "Variable \"" << identifier << "\" does not exist in the current scope";
                exit(EXIT_FAILURE);
            }

        default:
            match(IntegerLiteralToken, "Integer Literal");
            exit(EXIT_FAILURE);
    }
    return nullptr;
};

/**
 * Construct an AST via precendence climbing parsing
 */
ASTNode* Parser::parseExpression(int minimumPrecedence)
{
    ASTNode* left = parsePrimary(), * right;
    SyntaxType lookAhead = getCurrentToken().getSyntaxType();

    while (isBinaryOperator(lookAhead) && getOperatorPrecedence(lookAhead) > minimumPrecedence)
    {
        getNextToken();
        right = parseExpression(getOperatorPrecedence(lookAhead));
        left = new BinOpNode(left, getOperatorType(lookAhead), right);
        lookAhead = getCurrentToken().getSyntaxType();
        if (lookAhead == RightParenthesisToken || lookAhead == SemicolonToken)
        {
            return left;
        }
    }
    return left;
};

ASTNode* Parser::parseStatement()
{
    switch (getCurrentToken().getSyntaxType())
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
        case ReturnKeyword:
            return parseReturnStatement();
        case WhileKeywordToken:
            return parseWhileStatement();
        default:
            return parseExpressionStatement();
    }
    return nullptr;
}

ASTNode* Parser::parseCompoundStatement()
{
    match(LeftCurlyBraceToken, "{");
    std::vector<ASTNode*> statements;

    /**
     * When we encounter a block statement, we push a new scope onto the stack,
     * make it the child of the parent to resolve variables in nested scopes,
     * and increment the scope variable.
     */
    ScopeTreeNode* parent = scopeTreeStack.top(), * child = new ScopeTreeNode();
    scopeTreeStack.push(child);
    parent->addChild(child);
    scope++;

    //While inside the compound statement
    while (getCurrentToken().getSyntaxType() != RightCurlyBraceToken)
    {
        //Add each statement to the statement list
        statements.push_back(parseStatement());
    }
    match(RightCurlyBraceToken, "}");

    //When the scope ends, decrement the scope and pop the stack
    scope--;
    scopeTreeStack.pop();
    return new CompoundStatementNode(statements);
}

ASTNode* Parser::parseIfStatement()
{
    ASTNode* condition, * stmtBody, * elseBody = nullptr;

    //Parse the "if (condition)" portion
    match(IfToken, "if");
    match(LeftParenthesisToken, "(");
    condition = parseExpression(0);
    match(RightParenthesisToken, ")");

    //Parse the "then" portion of the if statement
    stmtBody = parseStatement();
    if (getCurrentToken().getSyntaxType() == ElseToken)
    {
        match(ElseToken, "else");
        elseBody = parseStatement();
    }
    return new IfStatementNode(condition, stmtBody, elseBody);
}

ASTNode* Parser::parsePrintStatement()
{
    ASTNode* contents = nullptr;
    match(PrintToken, "print");
    match(LeftParenthesisToken, "(");
    contents = parseExpression(0);
    match(RightParenthesisToken, ")");
    match(SemicolonToken, ";");
    return new PrintNode(contents);
}

ASTNode* Parser::parseVariableDeclarationStatement()
{
    ASTNode* rhs = nullptr;
    std::string identifier;
    SyntaxToken token = getCurrentToken();
    bool isVarType = false;
    Type t;
    switch (getCurrentToken().getSyntaxType())
    {
        case IntKeywordToken:
            match(IntKeywordToken, "int");
            t = IntegerPrimitive;
            break;
        case DoubleKeywordToken:
            match(DoubleKeywordToken, "double");
            break;
        case BoolKeywordToken:
            match(BoolKeywordToken, "bool");
            break;
        default:
            t = ImplicitVarType;
            match(VarKeywordToken, "var");
            isVarType = true;
            break;
    }
    token = getCurrentToken();
    match(IdentifierToken, "an identifer");
    identifier = token.getText();

    /**
     * Rather than checking the parent scope, we check the local scope
     * so that we can implement variable shadowing
     */
    if (scopeTreeStack.top()->getSymbolTable()[identifier])
    {
        std::cerr << "Error: Variable \"" << identifier << "\" already exists.\n";
        exit(EXIT_FAILURE);
    }
    scopeTreeStack.top()->addEntry(identifier, t);
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
        if (token.getSyntaxType() != EqualsToken)
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
    return new VariableDeclarationNode(new VariableNode(t, identifier), rhs, identifier);
}

ASTNode* Parser::parseReturnStatement()
{
    ASTNode* toReturn;
    match(ReturnKeyword, "return");
    toReturn = parseExpression(0);
    match(SemicolonToken, ";");
    return new ReturnNode(toReturn);
}

/**
 * Parses a function declaration including any parameters.
 */
ASTNode* Parser::parseFunctionDeclaration()
{
    Type returnType;
    ASTNode* body;
    std::string functionIdentifier, parameterIdentifier;
    std::vector<VariableNode*> parameterList;

    /**
     * When declaring a function, the parameters are made children of the global scope,
     * and the function body adds a new scope to the scope in which the parameters reside.
     */
    ScopeTreeNode* parent = scopeTreeStack.top(), * child = new ScopeTreeNode();
    scopeTreeStack.push(child);
    parent->addChild(child);
    scope++;

    //Determine the return type of the function
    switch (getCurrentToken().getSyntaxType())
    {
        case IntKeywordToken:
            returnType = IntegerPrimitive;
            match(IntKeywordToken, "int");
            break;
        case BoolKeywordToken:
            returnType = BooleanPrimitive;
            match(BoolKeywordToken, "bool");
            break;
    }

    //Match and obtain the function identifier
    if (getCurrentToken().getSyntaxType() == IdentifierToken)
    {
        functionIdentifier = getCurrentToken().getText();
        scopeTreeStack.top()->addEntry(functionIdentifier, returnType);
    }
    match(IdentifierToken, "an identifier");

    //Parse the function parameters (if any)
    match(LeftParenthesisToken, "(");
    while (getCurrentToken().getSyntaxType() != RightParenthesisToken)
    {
        match(IntKeywordToken, "int");

        /**
         * Obtain the parameter identifier, add it to the current scope's symbol table,
         * and add it to the function's argument list
         */
        parameterIdentifier = match(IdentifierToken, "an identifier").getText();
        parameterList.push_back(new VariableNode(IntegerPrimitive, parameterIdentifier));
        scopeTreeStack.top()->addEntry(parameterIdentifier, IntegerPrimitive);

        /**
         * If a comma is encountered, the next token cannot be a right semicolon
         */
        if (getCurrentToken().getSyntaxType() == CommaToken)
        {
            match(CommaToken, ",");
            //Ensure that the next token is NOT a right parenthesis
            if (getCurrentToken().getSyntaxType() == RightParenthesisToken)
            {
                std::cerr << "Error: Invalid function declaration syntax";
                exit(EXIT_FAILURE);
            }
        }
    }
    match(RightParenthesisToken, ")");

    //Parse the function body
    body = parseCompoundStatement();

    /**
     * At this point, the scope is returned to that of the function parameters,
     * so we pop the stack and decrement the scope to return to the global scope for
     * future function declarations
     */
    scopeTreeStack.pop();
    scope--;
    return new FunctionNode(functionIdentifier, returnType, parameterList, body);
}

ASTNode* Parser::parseExpressionStatement()
{
    ASTNode* expr = parseExpression(0);
    match(SemicolonToken, ";");
    return expr;
}

ASTNode* Parser::parseWhileStatement()
{
    ASTNode* condition, * body;

    //Parse the "while (condition)" portion
    match(WhileKeywordToken, "while");
    match(LeftParenthesisToken, "(");
    condition = parseExpression(0);
    match(RightParenthesisToken, ")");
    body = parseStatement();
    return new WhileNode(condition, body);

}

/**
 * Parses the program from start to finish by parsing functions as well as
 * global variable declarations.
 */
ASTNode* Parser::parseProgram()
{
    std::vector<ASTNode*> units;
    //While there are still tokens to be read in
    while (getCurrentToken().getSyntaxType() != EOFToken)
    {
        units.push_back(parseFunctionDeclaration());
    }
    return new ProgramNode(units);
}
