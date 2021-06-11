#include "../headers/SyntaxToken.h"
#include <string>

SyntaxToken::SyntaxToken(SyntaxType syntaxType, std::string text)
{
    this->syntaxType = syntaxType;
    this->text = text;
}

SyntaxToken::SyntaxToken(){}