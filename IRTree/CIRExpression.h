#pragma once

#include <iosfwd>
#include <bits/unique_ptr.h>
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

    class BinaryExpression : public IExpression {

    public:
        enum EBinaryType {
            AND,
            PLUS,
            MINUS,
            MULTIPLY
        };

        const EBinaryType binType;
        std::unique_ptr<IExpression> leftExp;
        std::unique_ptr<IExpression> rightExp;

        BinaryExpression( EBinaryType binaryType, IExpression* left, IExpression* right );

    private:

    };

    class MemoryExpression : public IExpression {

    public:
        std::unique_ptr<IExpression> exp;

        MemoryExpression( IExpression* exp );

    private:

    };

    class CallExpression : public IExpression {

    public:
        std::unique_ptr<IExpression> funcExp;
        std::unique_ptr<ExpList> args;

        CallExpression( IExpression* funcExp, ExpList* args );

    private:

    };

    class ESEQExpression : public IExpression {

    public:
        std::unique_ptr<IStatement> stm;
        std::unique_ptr<IExpression> exp;

        ESEQExpression( IStatement* stm, IExpression* exp );

    private:

    };
}
