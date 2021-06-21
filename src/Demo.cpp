#include <iostream>
#include <string>

#include "../headers/AstNode.h"
#include "../headers/Visitor.h"
#include "../headers/BinOpNode.h"
#include "../headers/IntNode.h"

#include "../headers/Parser.h"
#include "../headers/CompilerVisitor.h"
#include "../headers/VM.h"
#include "../headers/TypeCheckingVisitor.h"
#include "../headers/PrintVisitor.h"

using reg = int;
int main()
{
    CompilerVisitor v;
    TypeCheckingVisitor typeChecker;
    PrintVisitor p;
    Parser parser("in.txt");

    int a = 1;
    int b = 2;
    ASTNode* AST = parser.parseProgram();
    AST->accept(typeChecker);

    AST->accept(v);
    VM virtualMachine(v.getInstructions());
    //virtualMachine.dumpByteCode();
    virtualMachine.disassembleInstruction();
    virtualMachine.run();
    //AST->accept(p);
    return 0;
}