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

    BinaryExpression::BinaryExpression( EBinaryType binType, IExpression* left, IExpression* right ) :
            binType( binType ),
            leftExp( (std::unique_ptr<IExpression>&&) left ),
            rightExp( (std::unique_ptr<IExpression>&&) right )
    {
    }

    MemoryExpression::MemoryExpression( IExpression* exp ) :
            exp( (std::unique_ptr<IExpression>&&) exp )
    {
    }

    CallExpression::CallExpression( IExpression* funcExp, ExpList* args ) :
            funcExp( (std::unique_ptr<IExpression>&&) funcExp ),
            args( (std::unique_ptr<ExpList>&&) args )
    {
    }

    ESEQExpression::ESEQExpression( IStatement* stm, IExpression* exp ) :
            stm( (std::unique_ptr<IStatement>&&) stm ),
            exp( (std::unique_ptr<IExpression>&&) exp )
    {
    }

    int TempExpression::countAll = 0;
}