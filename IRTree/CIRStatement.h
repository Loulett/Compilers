#pragma once
#include <bits/unique_ptr.h>
#include <src/AST/ITreeNodes.h>
#include "IStatement.h"
#include "Label.h"
#include "CIRExpression.h"


namespace IRTree
{
    class MoveStatement : public IStatement
    {

    public:
        std::unique_ptr<IExpression> dst;
        std::unique_ptr<IExpression> src;

        MoveStatement( IExpression* dst, IExpression* src );

    private:
    };

    class ExpressionStatement : public IStatement
    {

    public:
        std::unique_ptr<IExpression> exp;

        ExpressionStatement( IExpression* exp );

    private:
    };

    class JumpStatement : public IStatement
    {

    public:
        std::unique_ptr<IExpression> exp;
        std::unique_ptr<TempList> targetList;

        JumpStatement( IExpression* exp, TempList* tempList );

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
        std::unique_ptr<IExpression> leftExp;
        std::unique_ptr<IExpression> rightExp;
        std::unique_ptr<Label> ifTrueLabel;
        std::unique_ptr<Label> ifFalseLabel;

        JumpStatement( ERelationType relType, IExpression* left, IExpression* right, Label* ifTrue, Label* ifFalse );

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
