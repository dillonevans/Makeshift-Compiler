#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

#include "../include/AstNode.h"
#include "../include/Parser.h"

#include "../include/PrintVisitor.h"
#include "../include/x86Visitor.h"
#include "../include/TypeCheckingVisitor.h"
#include "../include/GenTACVisitor.h"


void compile(std::string inFile, std::string outFile);
int main(int argc, char* argv[])
{

    compile(argv[1], argv[2]);
    return 0;
}

void compile(std::string inFile, std::string outFile)
{
    x86Visitor compiler;
    TypeCheckingVisitor typeChecker;
    PrintVisitor p;
    Parser parser("in.txt");
    ASTNode* AST = parser.parseProgram();
    AST->accept(compiler);
    GenTACVisitor gtv;
    AST->accept(gtv);
}

