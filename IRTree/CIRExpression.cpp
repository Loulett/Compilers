#include "CIRExpression.h"

namespace IRTree {
    ConstExpression::ConstExpression( const int value ) :
            value( value )
    {
    }

    NameExpression::NameExpression( Label* label ) :
            label(  label )
    {
    }

    TempExpression::TempExpression() :
            id( countAll++ ), name( "" ), tempType( ID )
    {
    }

    TempExpression::TempExpression( const std::string& name ) :
            id( countAll++ ), name( name ), tempType( NAME )
    {
    }

    BINOP::BINOP( EBinaryType binType, IExpr* left, IExpr* right ) :
        binType( binType ),
        leftExp(  left ),
        rightExp(  right )
    {
    }

    MemoryExpression::MemoryExpression( IExpr* exp ) :
            exp(  exp )
    {
    }


    CallExpression::CallExpression( IExpr* funcExp, ExpList* args ) :
            funcExp(  funcExp ),
            args(  args )
    {
    }

    ESEQExpression::ESEQExpression( IStatement* stm, IExpr* exp ) :
        stm(  stm ),
        exp(  exp )
    {
    }

    int TempExpression::countAll = 0;
}