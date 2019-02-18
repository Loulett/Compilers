#pragma once

#include "../Visitor.h"
#include "..ActivationRecords/IFrame.h"
#include "IStatement.h"

struct CCodeFragment {
    const IFrame* frame;
    const IRTree::IStatement* body;
};

class CTranslator : public IVisitor {

    std::vector<CCodeFragment> codeFragments;

    void visit( const CGoal* n ) override;
    void visit( const CMainClass* n ) override;
    void visit( const СClassDeclaration* n ) override;
    void visit( const CVarDeclaration* n ) override;
    void visit( const CArgument* n ) override;
    void visit( const CMethodDeclaration* n ) override;

    void visit( const CType* n ) override;

    void visit( const CIfStatement* n ) override;
    void visit( const CWhileStatement* n ) override;
    void visit( const CComplexStatement* n ) override;
    void visit( const CPrintStatement* n ) override;
    void visit( const CAssignmentStatement* n ) override;
    void visit( const CArrayAssignmentStatement* n ) override;

    void visit( const CBinaryExpression* n ) override;
    void visit( const CIndexExpression* n ) override;
    void visit( const CLengthExpression* n ) override;
    void visit( const CMethodCallExpression* n ) override;
    void visit( const CIntegerExpression* n ) override;
    void visit( const CBooleanConstExpression* n ) override;
    void visit( const CIdentifierExpression* n ) override;
    void visit( const CThisExpression* n ) override;
    void visit( const CNewArrExpression* n ) override;
    void visit( const CNewExpression* n ) override;
    void visit( const CNegationExpression* n ) override;
    void visit( const CParenthesesExpression* n ) override;

    void visit( const CIdentifier* n ) override;
};
