#include "../headers/SyntaxToken.h"
#include <string>

SyntaxToken::SyntaxToken(SyntaxType syntaxType, std::string text)
{
    this->syntaxType = syntaxType;
    this->text = text;
}

SyntaxToken::SyntaxToken() {}

std::string SyntaxToken::getText()
{
    return this->text;
}

SyntaxType SyntaxToken::getSyntaxType()
{
    return this->syntaxType;
}