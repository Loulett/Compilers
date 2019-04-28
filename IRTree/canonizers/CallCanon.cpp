#include <memory>

#include "CallCanon.h"


namespace IRT
{

    std::unique_ptr<const IRStatement> CallCanon::CanonicalTree()
    {
        return std::move( prevStm );
    }

    void CallCanon::updateLastExp( const IRExpression* newLastExp )
    {
        prevExp = std::move( std::unique_ptr<const IRExpression>( newLastExp ) );
    }

    void CallCanon::updateLastExp( std::unique_ptr<const IRExpression> newLastExp )
    {
        prevExp = std::move( newLastExp );
    }

    void CallCanon::updateLastExpList( const IRExpList* newLastExpList )
    {
        prevExpList = std::move( std::unique_ptr<const IRExpList>( newLastExpList ) );
    }

    void CallCanon::updateLastExpList( std::unique_ptr<IRExpList> newLastExpList )
    {
        prevExpList = std::move( newLastExpList );
    }

    void CallCanon::updateLastStm( const IRStatement* newLastStm )
    {
        prevStm = std::move( std::unique_ptr<const IRStatement>( newLastStm ) );
    }

    void CallCanon::updateLastStm( std::unique_ptr<const IRStatement> newLastStm )
    {
        prevStm = std::move( newLastStm );
    }

    void CallCanon::updateLastStmList( const CStmList* newLastStmList )
    {
        prevStmList = std::move( std::unique_ptr<const CStmList>( newLastStmList ) );
    }

    void CallCanon::updateLastStmList( std::unique_ptr<const CStmList> newLastStmList )
    {
        prevStmList = std::move( newLastStmList );
    }

    void CallCanon::Visit( const ConstExpression* n )
    {
        updateLastExp( std::make_unique<const ConstExpression>( n->GetValue() ) );
    }

    void CallCanon::Visit( const NameExpression* n )
    {
        updateLastExp( std::make_unique<const NameExpression>( n->GetLabel() ) );
    }

    void CallCanon::Visit( const TempExpression* n )
    {
        updateLastExp( std::make_unique<const TempExpression>( n->GetTemp() ) );
    }

    void CallCanon::Visit( const BinOpExpression* n )
    {
        n->GetLeft()->Accept( this );
        std::unique_ptr<const IRExpression> nLeft = std::move( prevExp );

        n->GetRight()->Accept( this );
        std::unique_ptr<const IRExpression> nRight = std::move( prevExp );

        updateLastExp(
                std::make_unique<const BinOpExpression>(
                        n->GetType(),
                        nLeft.release(),
                        nRight.release()
                )
        );
    }

    void CallCanon::Visit( const MemExpression* n )
    {
        n->GetMem()->Accept( this );
        std::unique_ptr<const IRExpression> addressExp = std::move( prevExp );

        updateLastExp(
                std::make_unique<const MemExpression>( addressExp.release() )
        );
    }

    void CallCanon::Visit( const CallExpression* n )
    {
        n->GetFuncExp()->Accept( this );
        std::unique_ptr<const IRExpression> functionExp = std::move( prevExp );

        n->GetArgs()->Accept(this);
        std::unique_ptr<const IRExpList> argumentsList = std::move( prevExpList );

        CTemp temp;
        updateLastExp(
                std::make_unique<const ESeqExpression>(
                        std::make_unique<const MoveStatement>(
                                std::make_unique<const TempExpression>( temp ),
                                std::make_unique<const CallExpression>(
                                        std::move( functionExp ),
                                        std::move( argumentsList )
                                )
                        ),
                        std::make_unique<const TempExpression>( temp )
                ) );
    }

    void CallCanon::Visit( const ESeqExpression* n )
    {
        n->GetStm()->Accept( this );
        n->GetExp()->Accept( this );

        updateLastExp(
                std::make_unique<const ESeqExpression>(
                        prevStm.get(),
                        prevExp.get()
                )
        );
    }

    void CallCanon::Visit( const ExpStatement* n )
    {
        n->GetExp()->Accept( this );
        std::unique_ptr<const IRExpression> exp = std::move( prevExp );

        updateLastStm(
                std::make_unique<const ExpStatement>( exp.release() )
        );
    }

    void CallCanon::Visit( const CJumpStatement* n )
    {
        n->GetLeft()->Accept( this );
        std::unique_ptr<const IRExpression> nLeft = std::move( prevExp );

        n->GetRight()->Accept( this );
        std::unique_ptr<const IRExpression> nRight = std::move( prevExp );

        updateLastStm(
                std::make_unique<const CJumpStatement>(
                        n->GetType(),
                        nLeft.release(),
                        nRight.release(),
                        n->GetTrueLabel(),
                        n->GetFalseLabel()
                )
        );
    }

    void CallCanon::Visit( const JumpStatement* n )
    {
        updateLastStm(
                std::make_unique<const JumpStatement>( n->GetLabel() )
        );
    }

    void CallCanon::Visit( const LabelStatement* n )
    {
        updateLastStm(
                std::make_unique<const LabelStatement>( n->GetLabel() )
        );
    }

    void CallCanon::Visit( const MoveStatement* n )
    {
        n->GetDst()->Accept( this );
        std::unique_ptr<const IRExpression> destination = std::move( prevExp );

        n->GetSrc()->Accept( this );
        std::unique_ptr<const IRExpression> source = std::move( prevExp );

        updateLastStm(
                std::make_unique<const MoveStatement>(
                        destination.release(),
                        source.release()
                )
        );
    }

    void CallCanon::Visit( const SeqStatement* n )
    {
        n->GetLeft()->Accept( this );
        std::unique_ptr<const IRStatement> nLeft = std::move( prevStm );

        n->GetRight()->Accept( this );
        std::unique_ptr<const IRStatement> nRight = std::move( prevStm );

        updateLastStm(
                std::make_unique<const SeqStatement>(
                        nLeft.release(),
                        nRight.release()
                )
        );
    }

    void CallCanon::Visit( const IRExpList* list )
    {
        auto newList = std::make_unique<IRExpList>();
        const auto& arguments = list->GetExpressions();
        for( const auto& arg : arguments ) {
            arg->Accept( this );
            newList->Add( std::move( prevExp ) );
        }

        updateLastExpList( std::move( newList ) );
    }

    void CallCanon::Visit( const CStmList* list )
    {
        auto newList = std::make_unique<CStmList>();
        const auto& arguments = list->GetStatements();
        for( const auto& arg : arguments ) {
            arg->Accept( this );
            newList->Add( std::move( prevStm ) );
        }

        updateLastStmList( std::move( newList ) );
    }

}
