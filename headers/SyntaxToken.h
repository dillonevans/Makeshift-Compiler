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
    AssignmentToken,
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
    LogicalOrToken,
    ReturnKeyword,
    CommaToken
};

class SyntaxToken
{
    private:
    std::string text;
    SyntaxType syntaxType;
    public:
    std::string getText();
    SyntaxType getSyntaxType();
    SyntaxToken(SyntaxType syntaxType, std::string text);
    SyntaxToken();
};

#endif