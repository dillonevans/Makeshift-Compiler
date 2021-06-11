#ifndef SYNTAXTOKEN_H
#define SYNTAXTOKEN_H
#include <string>
enum SyntaxType 
{
    AddToken, 
    MinusToken, 
    MultToken, 
    DivideToken, 
    EqualsToken,
    WhitespaceToken,
    EOFToken,
    IntegerLiteralToken,
    DoubleLiteralToken,
    LeftParenthesisToken,
    RightParenthesisToken,
    LeftCurlyBraceToken,
    RightCurlyBraceToken,
    SemicolonToken,
    IfToken,
    ElseToken,
    LessThanToken,
    LessThanOrEqualToToken,
    GreaterThanToken,
    GreaterThanOrEqualToToken,
    PrintToken,
    IdentifierToken,
    VarKeywordToken,
    IntKeywordToken,
    BoolKeywordToken,
    TrueKeywordToken,
    FalseKeywordToken,
    DoubleKeywordToken,
    BitwiseAndToken,
    LogicalAndToken,
    BitwiseOrToken,
    LogicalOrToken
};

class SyntaxToken
{
    public:
    std::string text;
    SyntaxType syntaxType;
    SyntaxToken(SyntaxType syntaxType, std::string text);
    SyntaxToken();
};

#endif