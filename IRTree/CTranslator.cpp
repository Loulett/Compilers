#include "CTranslator.h"
#include "CIRExpression.h"

using namespace IRTree;

//    MemoryExpression(BINOP(BINOP::PLUS, curFrame->FP(), ConstExpression()))

void CTranslator::visit( const CGoal* n )
{
    n->mainClass->Accept( this );

    for( const auto& clazz : *n->classDeclarations ) {
        clazz->Accept( this );
    }
}

void CTranslator::visit( const CMainClass* n )
{

}

void CTranslator::visit( const СClassDeclaration* n )
{

}

void CTranslator::visit( const CVarDeclaration* n )
{

}

void CTranslator::visit( const CArgument* n )
{

}

void CTranslator::visit( const CMethodDeclaration* n )
{

}


void CTranslator::visit( const CType* n )
{

}


void CTranslator::visit( const CIfStatement* n )
{

}

void CTranslator::visit( const CWhileStatement* n )
{

}

void CTranslator::visit( const CComplexStatement* n )
{

}

void CTranslator::visit( const CPrintStatement* n )
{

}

void CTranslator::visit( const CAssignmentStatement* n )
{

}

void CTranslator::visit( const CArrayAssignmentStatement* n )
{

}


void CTranslator::visit( const CBinaryExpression* n )
{

}

void CTranslator::visit( const CIndexExpression* n )
{

}

void CTranslator::visit( const CLengthExpression* n )
{

}

void CTranslator::visit( const CMethodCallExpression* n )
{

}

void CTranslator::visit( const CIntegerExpression* n )
{

}

void CTranslator::visit( const CBooleanConstExpression* n )
{

}

void CTranslator::visit( const CIdentifierExpression* n )
{

}

void CTranslator::visit( const CThisExpression* n )
{

}

void CTranslator::visit( const CNewArrExpression* n )
{

}

void CTranslator::visit( const CNewExpression* n )
{

}

void CTranslator::visit( const CNegationExpression* n )
{

}

void CTranslator::visit( const CParenthesesExpression* n )
{

}

void CTranslator::visit( const CIdentifier* n )
{

}
