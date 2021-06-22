#include "../headers/Local.h"

Local::Local(std::string identifier, int scope, int localOffset)
{
    this->identifier = identifier;
    this->scope = scope;
    this->localOffset = localOffset;
}

std::string Local::getIdentifier()
{
    return this->identifier;
}

int Local::getScope()
{
    return this->scope;
}