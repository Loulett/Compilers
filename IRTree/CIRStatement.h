#pragma once
#include <memory>
#include <src/AST/ITreeNodes.h>
#include "IStatement.h"
#include "Label.h"
#include "CIRExpression.h"


namespace IRTree
{
    class MoveStatement : public IStatement
    {

    public:
        std::unique_ptr<IExpr> dst;
        std::unique_ptr<IExpr> src;

        MoveStatement( IExpr* dst, IExpr* src );
    private:
    };

    class ExpressionStatement : public IStatement
    {

    public:
        std::unique_ptr<IExpr> exp;
        CExpressionStatement( IExpr* exp );

    private:
    };

    class JumpStatement : public IStatement
    {

    public:
        std::unique_ptr<IExpression> exp;
        std::unique_ptr<TempList> targetList;

        JumpStatement( IExpr* exp, TempList* tempList );

    private:
    };

    class JumpStatement : public IStatement
    {

    public:
        enum ERelationType {
            EQ,
            NOTEQ,
            LESS
        };

        const ERelationType relationType;
        std::unique_ptr<IExpr> leftExp;
        std::unique_ptr<IExpr> rightExp;
        std::unique_ptr<Label> ifTrueLabel;
        std::unique_ptr<Label> ifFalseLabel;

        JumpStatement( ERelationType relType, IExpr* left, IExpr* right, Label* ifTrue, Label* ifFalse );

    private:
    };

    class SeqStatement : public IStatement
    {

    public:
        std::unique_ptr<IStatement> leftStm;
        std::unique_ptr<IStatement> rightStm;

        SeqStatement( IStatement* left, IStatement* right );

    private:
    };

    class LabelStatement : public IStatement
    {

    public:
        std::unique_ptr<Label> label;

        LabelStatement( Label* label );

    private:
    };
}
