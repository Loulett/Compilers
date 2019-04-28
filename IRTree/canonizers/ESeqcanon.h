#pragma once

#include "IRVisitor.h"

namespace IRT
{
    class ESeqCanon : public IRVisitor
    {

    public:
        ESeqCanon() = default;

        std::unique_ptr<const IRStatement> CanonicalTree();
        std::unique_ptr<const IRStatement> CanonicalStmTree();
        std::unique_ptr<const IRExpression> CanonicalExpTree();

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

        void updateLastExpList( std::unique_ptr<const IRExpList> newLastExpList );

        void updateLastStm( const IRStatement* newLastStm );
        void updateLastStm( std::unique_ptr<const IRStatement> newLastStm );

        std::unique_ptr<const IRExpression> canonizeExpSubtree( std::unique_ptr<const IRExpression> exp ) const;
        std::unique_ptr<const IRStatement> canonizeStmSubtree( std::unique_ptr<const IRStatement> stm ) const;

        bool areCommuting( const IRStatement* stm, const IRExpression* exp );
        const CESeqExp* castToESeqExp( const IRExpression* exp );

        std::unique_ptr<const IRExpression> prevExp;
        std::unique_ptr<const IRStatement> prevStm;
        std::unique_ptr<const IRExpList> prevExpList;
//        std::unique_ptr<const CStmList> prevStmList;
    };

}
