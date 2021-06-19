#include "../headers/Lexer.h"
#include <iostream>
#include <sstream>
Lexer::Lexer(std::string text) : file{ text }
{
    std::stringstream buffer;
    buffer << file.rdbuf();
    this->text = buffer.str();
}

/**
 * Skips over any whitespace to reach the next token
 */
void Lexer::skipWhitespace()
{
    if (isspace(getCurrentChar()))
    {
        while (isspace(getCurrentChar()))
        {
            advance();
        }
    }
}

/**
 * Returns true if the end of the file is reached
 */
bool Lexer::hasReachedEOF()
{
    return position > text.size();
}

/**
 * Consumes the next token
 */
SyntaxToken Lexer::lex()
{
    int length;
    std::string lexeme;
    skipWhitespace();
    int start = position;

    if (isdigit(getCurrentChar()))
    {
        while (isdigit(getCurrentChar()))
        {
            advance();
        }
        length = position - start;
        lexeme = text.substr(start, length);
        return SyntaxToken(IntegerLiteralToken, lexeme);
    }
    else if (isalpha(getCurrentChar()))
    {
        while (isalpha(getCurrentChar()))
        {
            advance();
        }
        length = position - start;
        lexeme = text.substr(start, length);
        switch (lexeme[0]) //Micro optimization: Check first character for faster look up
        {
            case 'b':
                if (lexeme == "bool")
                {
                    return SyntaxToken(BoolKeywordToken, lexeme);
                }
                break;
            case 'd':
                if (lexeme == "double") {
                    return SyntaxToken(DoubleKeywordToken, lexeme);
                }
                break;
            case 'e':
                if (lexeme == "else") {
                    return SyntaxToken(ElseToken, lexeme);
                }
                break;
            case 'f':
                if (lexeme == "false") {
                    return SyntaxToken(FalseKeywordToken, lexeme);
                }
            case 'i':
                if (lexeme == "if") {
                    return SyntaxToken(IfToken, lexeme);
                }
                else if (lexeme == "int") {
                    return SyntaxToken(IntKeywordToken, lexeme);
                }
                break;
            case 'p':
                if (lexeme == "print") {
                    return SyntaxToken(PrintToken, lexeme);
                }
                break;
            case 'r':
                if (lexeme == "return") {
                    return SyntaxToken(ReturnKeyword, lexeme);
                }
            case 't':
                if (lexeme == "true") {
                    return SyntaxToken(TrueKeywordToken, lexeme);
                }
                break;
            case 'v':
                if (lexeme == "var") {
                    return SyntaxToken(VarKeywordToken, lexeme);
                }
                break;
        }
        return SyntaxToken(IdentifierToken, lexeme);
    }
    else
    {
        auto current = getCurrentChar();
        advance();
        switch (current)
        {
            case '+':
                return SyntaxToken(AddToken, "+");
            case '-':
                return SyntaxToken(MinusToken, "-");
            case '*':
                return SyntaxToken(MultToken, "*");
            case '/':
                return SyntaxToken(DivideToken, "/");
            case '=':
                if (getCurrentChar() == '=')
                {
                    advance();
                    return SyntaxToken(EqualsToken, "==");
                }
                return SyntaxToken(EqualsToken, "=");
            case '(':
                return SyntaxToken(LeftParenthesisToken, "(");
            case ')':
                return SyntaxToken(RightParenthesisToken, ")");
            case '{':
                return SyntaxToken(LeftCurlyBraceToken, "{");
            case '}':
                return SyntaxToken(RightCurlyBraceToken, "}");
            case ',':
                return SyntaxToken(CommaToken, ",");
            case ';':
                return SyntaxToken(SemicolonToken, ";");
            case '<':
                if (getCurrentChar() == '=')
                {
                    advance();
                    return SyntaxToken(LessThanOrEqualToToken, "<=");
                }
                return SyntaxToken(LessThanToken, "<");
            case '>':
                if (getCurrentChar() == '=')
                {
                    advance();
                    return SyntaxToken(GreaterThanOrEqualToToken, ">=");
                }
                return SyntaxToken(GreaterThanToken, ">");
            case '&':
                if (getCurrentChar() == '&')
                {
                    advance();
                    return SyntaxToken(LogicalAndToken, "&&");
                }
                return SyntaxToken(BitwiseAndToken, "&&");
                break;
            case '|':
                if (!hasReachedEOF())
                {
                    if (getCurrentChar() == '|')
                    {
                        advance();
                        return SyntaxToken(LogicalOrToken, "||");
                    }
                }
                return SyntaxToken(BitwiseOrToken, "||");
                break;
            case '\0':
                return SyntaxToken(EOFToken, "EOF");
            default:
                exit(EXIT_FAILURE);
        }
    }
};

/**
 * Retrieves the current character
 */
char Lexer::getCurrentChar()
{
    if (position < text.size())
        return text[position];
    else
        return '\0';
}

/**
 * Advances to the next character
 */
void Lexer::advance()
{
    position++;
}
