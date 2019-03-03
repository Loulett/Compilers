#include "CTranslator.h"
#include "CIRExpression.h"

using namespace IRTree;

//    MemoryExpression(BINOP(BINOP::PLUS, curFrame->FP(), ConstExpression()))

void CTranslator::visit( const Goal* n )
{
    n->mainClass->Accept( this );

    for( const auto& clazz : *n->classDeclarations ) {
        clazz->Accept( this );
    }
}

void CTranslator::visit( const MainClass* n )
{

}

void CTranslator::visit( const СlassDeclaration* n )
{

}

void CTranslator::visit( const VarDeclaration* n )
{

}

void CTranslator::visit( const Argument* n )
{

}

void CTranslator::visit( const MethodDeclaration* n )
{

}


void CTranslator::visit( const Type* n )
{

}


void CTranslator::visit( const IfStatement* n )
{

}

void CTranslator::visit( const WhileStatement* n )
{

}

void CTranslator::visit( const ComplexStatement* n )
{

}

void CTranslator::visit( const PrintStatement* n )
{

}

void CTranslator::visit( const AssignmentStatement* n )
{
    IRTree::IStatement lvalue;
    IRTree::IExpr rvalue;

}

void CTranslator::visit( const ArrayAssignmentStatement* n )
{

}


void CTranslator::visit( const BinaryExpression* n )
{

}

void CTranslator::visit( const IndexExpression* n )
{

}

void CTranslator::visit( const LengthExpression* n )
{

}

void CTranslator::visit( const MethodCallExpression* n )
{

}

void CTranslator::visit( const IntegerExpression* n )
{

}

void CTranslator::visit( const BooleanConstExpression* n )
{

}

void CTranslator::visit( const IdentifierExpression* n )
{

}

void CTranslator::visit( const ThisExpression* n )
{

}

void CTranslator::visit( const NewArrExpression* n )
{

}

void CTranslator::visit( const NewExpression* n )
{

}

void CTranslator::visit( const NegationExpression* n )
{

}

void CTranslator::visit( const ParenthesesExpression* n )
{

}

void CTranslator::visit( const Identifier* n )
{

}
