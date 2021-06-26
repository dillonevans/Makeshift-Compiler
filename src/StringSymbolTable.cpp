#include "../include/StringSymbolTable.h"
#include <iostream>
int StringSymbolTable::labelCount{ 0 };
std::unordered_map<std::string, int> StringSymbolTable::table{};
void StringSymbolTable::addEntry(std::string text)
{
    table[text] = labelCount++;
}

int StringSymbolTable::getStringLabel(std::string text)
{
    return table[text];
}

int StringSymbolTable::getStringCount()
{
    return labelCount;
}