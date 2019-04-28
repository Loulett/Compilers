#pragma once

#include "IRVisitor.h"


namespace IRT
{
    class CallCanon : public IRVisitor
    {

    public:
        CallCanon() = default;

        std::unique_ptr<const IRStatement> CanonicalTree();

        void Visit( const ConstExpression* n ) override;
        void Visit( const NameExpression* n ) override;
        void Visit( const TempExpression* n ) override;
        void Visit( const BinOpExpression* n ) override;
        void Visit( const MemExpression* n ) override;
        void Visit( const CallExpression* n ) override;

        void Visit( const ESeqExpression* n ) override;

        void Visit( const MoveStatement* n ) override;  //+
        void Visit( const ExpStatement* n ) override;  //+
        void Visit( const JumpStatement* n ) override;  //+
        void Visit( const CJumpStatement* n ) override;  //+
        void Visit( const SeqStatement* n ) override;  //+
        void Visit( const LabelStatement* n ) override;  //+

        void Visit( const IRExpList* list ) override;  //+
        //void Visit( const CStmList* list ) override;

    private:
        void updateLastExp( const IRExpression* newLastExp );
        void updateLastExp( std::unique_ptr<const IRExpression> newLastExp );

        void updateLastExpList( const IRExpList* newLastExpList );
        void updateLastExpList( std::unique_ptr<IRExpList> newLastExpList );

        void updateLastStm( const IRStatement* newLastStm );
        void updateLastStm( std::unique_ptr<const IRStatement> newLastStm );

//        void updateLastStmList( const CStmList* newLastStmList );
//        void updateLastStmList( std::unique_ptr<const CStmList> newLastStmList );

        std::unique_ptr<const IRExpList> prevExpList;
        std::unique_ptr<const IRExpression> prevExp;
        std::unique_ptr<const IRStatement> prevStm;
//        std::unique_ptr<const CStmList> prevStmList;
    };

}
