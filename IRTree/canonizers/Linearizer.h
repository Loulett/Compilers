#pragma once

#include "../IRVisitor.h"


namespace IRT
{
    class Linearizer : public IRVisitor
    {

    public:
        Linearizer();

        std::unique_ptr<const IRStatement> CanonicalTree();

        void visit( const ConstExpression* n ) override;
        void visit( const NameExpression* n ) override;
        void visit( const TempExpression* n ) override;
        void visit( const BinOpExpression* n ) override;
        void visit( const MemExpression* n ) override;
        void visit( const CallExpression* n ) override;

        void visit( const ESeqExpression* n ) override;

        void visit( const MoveStatement* n ) override;
        void visit( const ExpStatement* n ) override;
        void visit( const JumpStatement* n ) override;
        void visit( const CJumpStatement* n ) override;
        void visit( const SeqStatement* n ) override;
        void visit( const LabelStatement* n ) override;

        void visit( const IRExpList* list ) override;
        void visit( const IRStatementList* list ) override;

    private:
        void updateLastExp( const IRExpression* newLastExp );
        void updateLastExp( std::unique_ptr<const IRExpression> newLastExp );

        void updateLastExpList( const IRExpList* newLastExpList );
        void updateLastExpList( std::unique_ptr<IRExpList> newLastExpList );

        void updateLastStm( const IRStatement* newLastStm );
        void updateLastStm( std::unique_ptr<const IRStatement> newLastStm );

        void saveCreatedStm( std::unique_ptr<const IRStatement> result );

        std::vector<std::vector<std::unique_ptr<const IRStatement>>> stackOfSeqChildren;
        std::vector<int> stackDepthCounter;

        std::unique_ptr<const IRExpList> prevExpList;
        std::unique_ptr<const IRExpression> prevExp;
        std::unique_ptr<const IRStatement> prevStm;
    };

}
