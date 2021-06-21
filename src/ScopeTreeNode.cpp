#include "../headers/ScopeTreeNode.h"
#include <iostream>

void ScopeTreeNode::addEntry(std::string identifier, Type t, ASTNode* node, bool isFunction)
{
    this->symbolTable[identifier] = std::tuple<Type, ASTNode*, bool>(t, node, isFunction);
}

void ScopeTreeNode::addChild(ScopeTreeNode* node)
{
    children.push_back(node);
    node->setParent(this);
}

std::list<ScopeTreeNode*> ScopeTreeNode::getChildren()
{
    return this->children;
}

std::unordered_map <std::string, std::tuple<Type, ASTNode*, bool>> ScopeTreeNode::getSymbolTable()
{
    return this->symbolTable;
}

ScopeTreeNode* ScopeTreeNode::getParentNode()
{
    return this->parent;
}

void ScopeTreeNode::setParent(ScopeTreeNode* parent)
{
    this->parent = parent;
}

ASTNode* ScopeTreeNode::getNode(std::string identifier)
{
    return std::get<1>(this->symbolTable[identifier]);
}

bool ScopeTreeNode::isFunction(std::string identifier)
{
    return std::get<2>(this->symbolTable[identifier]);
}
