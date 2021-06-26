#include <iostream>
#include <string>

#include "../headers/AstNode.h"
#include "../headers/Parser.h"
#include "../headers/TypeCheckingVisitor.h"
#include "../headers/PrintVisitor.h"
#include "../headers/x86Visitor.h"


void compile(std::string inFile, std::string outFile);
int main(int argc, char *argv[])
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
}
