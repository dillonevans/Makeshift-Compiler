#ifndef LOCAL_H
#define LOCAL_H
#include <string>
class Local
{
private:
    std::string identifier;
    int scope;

public:
    Local(std::string identifier, int scope, int localOffset);
    std::string getIdentifier();
    int getScope();
    int localOffset;
};

#endif