#ifndef LEXER_H
#define LEXER_H
#include <string>
#include "SyntaxToken.h"
#include <fstream>
class Lexer
{
    private:
    int position = 0;
    std::string text;
    std::ifstream file;
    char getCurrentChar();
    void skipWhitespace();

    public: 
    bool hasReachedEOF();
    void advance();
    SyntaxToken lex();
    Lexer(std::string text);
};
#endif