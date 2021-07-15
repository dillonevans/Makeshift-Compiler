#ifndef STRING_SYMBOL_TABLE_H
#define STRING_SYMBOL_TABLE_H
#include <string>
#include <unordered_map>
namespace StringSymbolTable
{
        extern int labelCount;
        extern std::unordered_map<std::string, int> table;
        void addEntry(std::string text);
        int getStringLabel(std::string text);
        int getStringCount();
};
#endif