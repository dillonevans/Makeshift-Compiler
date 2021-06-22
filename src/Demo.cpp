#include <iostream>
#include <string>

#include "../headers/AstNode.h"
#include "../headers/Visitor.h"
#include "../headers/BinOpNode.h"
#include "../headers/IntNode.h"

#include "../headers/Parser.h"
#include "../headers/TypeCheckingVisitor.h"
#include "../headers/PrintVisitor.h"
#include "../headers/x86Visitor.h"


using reg = int;
int main()
{

    x86Visitor compiler;
    TypeCheckingVisitor typeChecker;
    PrintVisitor p;
    Parser parser("in.txt");

    ASTNode* AST = parser.parseProgram();
    AST->accept(typeChecker);
    AST->accept(p);
    AST->accept(compiler);
    return 0;
}