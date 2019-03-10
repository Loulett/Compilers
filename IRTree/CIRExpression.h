#pragma once

#include <iosfwd>
#include <memory>
#include <src/AST/ITreeNodes.h>
#include "IExpression.h"
#include "IStatement.h"
#include "Label.h"
#include "List.h"


namespace IRTree {
    class ConstExpression : public IExpression {

    public:
        const int value;

        ConstExpression( const int value );

    private:
    };

    class NameExpression : public IExpression {

    public:
        std::unique_ptr<Label> label;

        NameExpression( Label* label );

    private:
    };

    class TempExpression : public IExpression {

    public:
        enum ETempType {
            ID,
            NAME
        };
        ETempType tempType;

        const int id;
        const std::string name;

        TempExpression();
        TempExpression( const std::string &name );

    private:
        static int countAll;

    };

    typedef std::vector<std::unique_ptr<TempExpression>> TempList;

    class BINOP : public IExpr
    {
    public:
        enum EBinaryType {
            AND,
            PLUS,
            MINUS,
            MULTIPLY
        };

        const EBinaryType binType;
        std::unique_ptr<IExpr> leftExp;
        std::unique_ptr<IExpr> rightExp;


        BINOP( EBinaryType binaryType, IExpr* left, IExpr* right );

    private:

    };

    class MemoryExpression : public IExpression {

    public:
        std::unique_ptr<IExpr> exp;

        CMemoryExpression( IExpr* exp );

    private:
    };

    class CCallExpression : public IExpr {
    public:
        std::unique_ptr<IExpr> funcExp;
        std::unique_ptr<ExpressionsList> args;

        CallExpression( IExpr* funcExp, ExpressionsList* args );

    private:

    };

    class ESEQExpression : public IExpression {

    public:
        std::unique_ptr<IStatement> stm;
        std::unique_ptr<IExpr> exp;

        ESEQExpression( IStatement* stm, IExpr* exp );

    private:

    };
}
