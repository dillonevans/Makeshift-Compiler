#include "../headers/Local.h"

Local::Local(std::string identifier, int scope)
{
    this->identifier = identifier;
    this->scope = scope;
}

std::string Local::getIdentifier()
{
    return this->identifier;
}

int Local::getScope()
{
    return this->scope;
}