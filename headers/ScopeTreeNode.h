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
    std::unordered_map<std::string, std::tuple<Type, ASTNode*, bool>> symbolTable;

public:
    ScopeTreeNode* getParentNode();
    std::list<ScopeTreeNode*> getChildren();
    std::unordered_map <std::string, std::tuple<Type, ASTNode*, bool>> getSymbolTable();
    void addEntry(std::string identifier, Type type, ASTNode* node, bool isFunction);
    void addChild(ScopeTreeNode* childNode);
    void setParent(ScopeTreeNode* parent);
    ASTNode* getNode(std::string identifier);
    bool isFunction(std::string identifier);
};
#endif