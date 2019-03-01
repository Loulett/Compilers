#include "CIRExpression.h"

namespace IRTree {
    ConstExpression::ConstExpression( const int value ) :
            value( value )
    {
    }

    NameExpression::NameExpression( Label* label ) :
            label( (std::unique_ptr<Label>&&) label )
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
        leftExp( (std::unique_ptr<IExpr>&&) left ),
        rightExp( (std::unique_ptr<IExpr>&&) right )
    {
    }

    MemoryExpression::MemoryExpression( IExpr* exp ) :
            exp( (std::unique_ptr<IExpr>&&) exp )

    {
    }


    CallExpression::CallExpression( IExpr* funcExp, ExpList* args ) :
            funcExp( (std::unique_ptr<IExpr>&&) funcExp ),
            args( (std::unique_ptr<ExpList>&&) args )
    {
    }

    ESEQExpression::ESEQExpression( IStatement* stm, IExpr* exp ) :
        stm( (std::unique_ptr<IStatement>&&) stm ),
        exp( (std::unique_ptr<IExpr>&&) exp )
    {
    }

    int TempExpression::countAll = 0;
}