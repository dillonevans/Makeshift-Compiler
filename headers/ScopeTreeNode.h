#ifndef SCOPETREENODE_H
#define SCOPETREENODE_H
#include "Value.h"
#include <unordered_map>
#include <string>
#include <list>
class ScopeTreeNode
{
    private:
    ScopeTreeNode* parent;
    std::list<ScopeTreeNode*> children;
    std::unordered_map<std::string, Type> symbolTable;

    public:
    ScopeTreeNode* getParentNode();
    std::list<ScopeTreeNode*> getChildren();
    std::unordered_map<std::string, Type> getSymbolTable();
    void addChild(std::string identifier, Type type);
    void setParent(ScopeTreeNode *parent);
};
#endif