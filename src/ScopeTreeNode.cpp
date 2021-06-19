#include "../headers/ScopeTreeNode.h"
#include <iostream>
void ScopeTreeNode::addEntry(std::string identifier, Type t, VariableNode* node)
{

    this->symbolTable[identifier] = std::pair<Type, VariableNode*>(t, node);
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

std::unordered_map <std::string, std::pair<Type, VariableNode*>> ScopeTreeNode::getSymbolTable()
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

VariableNode* ScopeTreeNode::getVariableNode(std::string identifier)
{
    return this->symbolTable[identifier].second;
}
