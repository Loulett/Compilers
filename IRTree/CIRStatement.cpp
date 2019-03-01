#include "CIRStatement.h"

namespace IRTree {
    MoveStatement::MoveStatement( IExpr* dst, IExpr* src ) :
            dst( dst ),
            src( (std::unique_ptr<IExpr>&&) src )
    {
    }


    ExpressionStatement::ExpressionStatement( IExpr* exp) :
            exp( (std::unique_ptr<IExpr>&&) exp )
    {
    }


    JumpStatement::JumpStatement( IExpr* exp, TempList* tempList ) :
            exp( (std::unique_ptr<IExpr>&&) exp )
            targetList( (std::unique_ptr<TempList>&&) tempList )
    {
    }

    CJumpStatement::CCJumpStatement( ERelationType relType, IExpr* left, IExpr* right, Label* ifTrue, Label* ifFalse ) :
            relationType( relType ),
            leftExp( (std::unique_ptr<IExpr>&&) left ),
            rightExp( (std::unique_ptr<IExpr>&&) right ),
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
