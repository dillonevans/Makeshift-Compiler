#ifndef SCOPETREENODE_H
#define SCOPETREENODE_H
#include "Value.h"
#include <unordered_map>
#include <string>
#include <list>
class ScopeTreeNode
{
private:
    ScopeTreeNode* parent = nullptr;
    std::list<ScopeTreeNode*> children;
    std::unordered_map<std::string, Type> symbolTable;

public:
    ScopeTreeNode* getParentNode();
    std::list<ScopeTreeNode*> getChildren();
    std::unordered_map<std::string, Type> getSymbolTable();
    void addEntry(std::string identifier, Type type);
    void addChild(ScopeTreeNode* childNode);
    void setParent(ScopeTreeNode* parent);
};
#endif