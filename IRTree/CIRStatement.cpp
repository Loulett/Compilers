#include "CIRStatement.h"

namespace IRTree {
    MoveStatement::MoveStatement( IExpression* dst, IExpression* src ) :
            dst( (std::unique_ptr<IExpression>&&) dst ),
            src( (std::unique_ptr<IExpression>&&) src )
    {
    }

    ExpressionStatement::ExpressionStatement( IExpression* exp) :
            exp( (std::unique_ptr<IExpression>&&) exp )
    {
    }

    JumpStatement::JumpStatement( IExpression* exp, TempList* tempList ) :
            exp( (std::unique_ptr<IExpression>&&) exp ),
            targetList( (std::unique_ptr<TempList>&&) tempList )
    {
    }

    JumpStatement::JumpStatement( ERelationType relType, IExpression* left, IExpression* right, Label* ifTrue, Label* ifFalse ) :
            relationType( relType ),
            leftExp( (std::unique_ptr<IExpression>&&) left ),
            rightExp( (std::unique_ptr<IExpression>&&) right ),
            ifTrueLabel( (std::unique_ptr<Label>&&) ifTrue ),
            ifFalseLabel( (std::unique_ptr<Label>&&) ifFalse )
    {
    }

    SeqStatement::SeqStatement( IStatement* left, IStatement* right) :
            leftStm( (std::unique_ptr<IStatement>&&) left ),
            rightStm( (std::unique_ptr<IStatement>&&) right )
    {
    }

    LabelStatement::LabelStatement( Label* label ) :
            label( (std::unique_ptr<Label>&&) label )
    {
    }
}
