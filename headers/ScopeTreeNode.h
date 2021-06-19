#ifndef SCOPETREENODE_H
#define SCOPETREENODE_H
#include "Value.h"
#include "VariableNode.h"
#include <unordered_map>
#include <string>
#include <list>
class ScopeTreeNode
{
private:
    ScopeTreeNode* parent = nullptr;
    std::list<ScopeTreeNode*> children;
    std::unordered_map<std::string, std::pair<Type, VariableNode*>> symbolTable;

public:
    ScopeTreeNode* getParentNode();
    std::list<ScopeTreeNode*> getChildren();
    std::unordered_map <std::string, std::pair<Type, VariableNode*>> getSymbolTable();
    void addEntry(std::string identifier, Type type, VariableNode* node);
    void addChild(ScopeTreeNode* childNode);
    void setParent(ScopeTreeNode* parent);
    VariableNode* getVariableNode(std::string);
};
#endif