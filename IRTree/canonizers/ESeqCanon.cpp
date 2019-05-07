#include "ESeqCanon.h"
#include <cassert>
#include <iostream>


namespace IRT
{

    std::unique_ptr<const IRStatement> ESeqCanon::CanonicalTree()
    {
        std::cout << "23\n";
        return std::move( CanonicalStmTree() );
    }

    std::unique_ptr<const IRStatement> ESeqCanon::CanonicalStmTree()
    {
        std::cout << "22\n";
        return std::move( prevStm );
    }

    std::unique_ptr<const IRExpression> ESeqCanon::CanonicalExpTree()
    {
        std::cout << "21\n";
        return std::move( prevExp );
    }

    void ESeqCanon::updateLastExp( const IRExpression* newLastExp )
    {
        std::cout << "20\n";
        prevExp = std::move( std::unique_ptr<const IRExpression>( newLastExp ) );
    }

    void ESeqCanon::updateLastExp( std::unique_ptr<const IRExpression> newLastExp )
    {
        std::cout << "19\n";
        prevExp = std::move( newLastExp );
    }

    void ESeqCanon::updateLastExpList( std::unique_ptr<const IRExpList> newLastExpList )
    {
        std::cout << "18\n";
        prevExpList = std::move( newLastExpList );
    }

    void ESeqCanon::updateLastStm( std::unique_ptr<const IRStatement> newLastStm )
    {
        std::cout << "17\n";
        prevStm = std::move( newLastStm );
        std::cout << "17end!\n";
    }

    std::unique_ptr<const IRExpression> ESeqCanon::canonizeExpSubtree( std::unique_ptr<const IRExpression> exp ) const
    {
        std::cout << "16\n";
        ESeqCanon visitor;
        exp->Accept( &visitor );
        return visitor.CanonicalExpTree();
    }

    std::unique_ptr<const IRStatement> ESeqCanon::canonizeStmSubtree( std::unique_ptr<const IRStatement> stm ) const
    {
        std::cout << "15\n";
        ESeqCanon visitor;
        stm->Accept( &visitor );
        return visitor.CanonicalStmTree();
    }

    bool ESeqCanon::areCommuting( const IRStatement* stm, const IRExpression* exp )
    {
        std::cout << "9\n";
        assert( stm != nullptr && exp != nullptr );
        std::cout << "9assert done\n";
        auto expStm = dynamic_cast<const ExpStatement* >( stm );
        std::cout << "9dynamic_cast done\n";
        bool isStmEmpty = expStm != nullptr &&
                          dynamic_cast<const ConstExpression* >( expStm->GetExp() ) != nullptr;
        std::cout << "end9\n";
        return isStmEmpty ||
               dynamic_cast<const ConstExpression*>( exp ) != nullptr ||
               dynamic_cast<const NameExpression*>( exp ) != nullptr;
    }

    const ESeqExpression* ESeqCanon::castToESeqExp( const IRExpression* exp )
    {
        std::cout << "14\n";
        return dynamic_cast<const ESeqExpression*>( exp );
    }

    void ESeqCanon::visit( const ConstExpression* n )
    {
        std::cout << "13\n";
        updateLastExp( std::make_unique<const ConstExpression>( n->value ) );
    }

    void ESeqCanon::visit( const NameExpression* n )
    {
        std::cout << "12\n";
        updateLastExp( std::make_unique<const NameExpression>( n->GetLabel() ) );
    }

    void ESeqCanon::visit( const TempExpression* n )
    {
        static int numEntries = 0;
        std::cout << numEntries << " num_entries " << std::endl;
        updateLastExp( std::move( std::make_unique<const TempExpression>( n->GetTemp() ) ) );
        numEntries++;
    }

    void ESeqCanon::visit( const BinOpExpression* n )
    {
        std::cout << "8\n";
        n->left->Accept( this );
        std::unique_ptr<const IRExpression> canonLeft = std::move( prevExp );
        n->right->Accept( this );
        std::unique_ptr<const IRExpression> canonRight = std::move( prevExp );

        const ESeqExpression* eseqLeft = castToESeqExp( canonLeft.get() );
        const ESeqExpression* eseqRight = castToESeqExp( canonRight.get() );

        std::unique_ptr<const IRExpression> resultExp;
        if( eseqLeft ) {
            resultExp = std::move( std::make_unique<const ESeqExpression>(
                    eseqLeft->GetStm()->GetCopy(),
                    std::move( std::make_unique<const BinOpExpression>(
                            n->binop,
                            eseqLeft->GetExp()->GetCopy(),
                            std::move( canonRight ) ) ) ) );
            if( eseqRight ) {
                resultExp = canonizeExpSubtree( std::move( resultExp ) );
            }
        } else if( eseqRight ) {
            if( areCommuting( eseqRight->GetStm(), canonLeft.get() ) ) {
                resultExp = std::move( std::make_unique<const ESeqExpression>(
                        eseqRight->GetStm()->GetCopy(),
                        std::move( std::make_unique<const BinOpExpression>(
                                n->binop,
                                std::move( canonLeft ),
                                eseqRight->GetExp()->GetCopy() ) ) ) );
            } else {
                Temp temp;
                resultExp = std::move( std::make_unique<const ESeqExpression>(
                        std::move( std::make_unique<const MoveStatement>(
                                std::move( std::make_unique<const TempExpression>( temp ) ),
                                std::move( canonLeft ) ) ),
                        std::move( std::make_unique<const ESeqExpression>(
                                eseqRight->GetStm()->GetCopy(),
                                std::move( std::make_unique<const BinOpExpression>(
                                        n->binop,
                                        std::move( std::make_unique<const TempExpression>( temp ) ),
                                        eseqRight->GetExp()->GetCopy() ) ) ) ) ) );
                resultExp = std::move( canonizeExpSubtree( std::move( resultExp ) ) );
            }
        } else {
            resultExp = std::move( std::make_unique<const BinOpExpression>(
                    n->binop,
                    canonLeft.release(),
                    canonRight.release() ) );
        }

        updateLastExp( resultExp.release() );
        std::cout << "8end\n";
    }

    void ESeqCanon::visit( const MemExpression* n )
    {
        std::cout << "7,5\n";
        n->expr->Accept( this );
        std::unique_ptr<const IRExpression> canonAddr = std::move( prevExp );

        const ESeqExpression* eseqAddr = castToESeqExp( canonAddr.get() );
        std::unique_ptr<const IRExpression> resultExp = nullptr;
        if( eseqAddr ) {
            resultExp = std::move( std::make_unique<const ESeqExpression>(
                    eseqAddr->GetStm()->GetCopy(),
                    std::move( std::make_unique<MemExpression>( eseqAddr->GetExp()->GetCopy() ) ) ) );
        } else {
            resultExp = std::move( std::make_unique<const MemExpression>( canonAddr.release() ) );
        }
        updateLastExp( resultExp.release() );
        std::cout << "7,5end\n";
    }

    void ESeqCanon::visit( const CallExpression* n )
    {
        std::cout << "7\n";
        n->func->Accept( this );
        std::unique_ptr<const IRExpression> canonFunc = std::move( prevExp );

        n->args->Accept( this );
        std::vector<std::unique_ptr<const IRStatement>> newStms;

        std::unique_ptr<IRExpList> newArgs = std::make_unique<IRExpList>();
        std::unique_ptr<const IRExpList> canonArgList = std::move( prevExpList );
        for( auto& canonArg : canonArgList->list ) {
            const ESeqExpression* eseqArg = castToESeqExp( canonArg.get() );
            if( eseqArg ) {
                newStms.push_back( eseqArg->GetStm()->GetCopy() );
            }

            Temp temp;
            newArgs->Add( new TempExpression( temp ) );

            std::unique_ptr<const IRExpression> moveSrcExp;
            if( eseqArg ) {
                moveSrcExp = eseqArg->GetExp()->GetCopy();
            } else {
                moveSrcExp = canonArg->GetCopy();
            }
            std::unique_ptr<const IRStatement> moveStm = std::move( std::make_unique<const MoveStatement>(
                    std::move( std::make_unique<const TempExpression>( temp ) ),
                    std::move( moveSrcExp ) ) );
            newStms.push_back( std::move( moveStm ) );
        }

        std::unique_ptr<const IRExpression> resultExp;
        if( !newStms.empty() ) {
            std::unique_ptr<const IRStatement> suffStm = std::move( newStms.back() );
            newStms.pop_back();
            for( int i = newStms.size() - 1; i >= 0 ; i-- ) {
                suffStm = std::move( std::make_unique<const SeqStatement>(
                        std::move( newStms[i] ) ,
                        std::move( suffStm )));
            }

            resultExp = std::move( std::make_unique<const ESeqExpression>(
                    std::move( suffStm ),
                    std::move( std::make_unique<const CallExpression>(
                            std::move( canonFunc ),
                            std::move( newArgs ) ) ) ) );
        } else {
            resultExp = std::move( std::make_unique<const CallExpression>(
                    std::move( canonFunc ),
                    std::move( canonArgList ) ) );
        }

        updateLastExp( std::move( resultExp ) );
        std::cout << "7end\n";
    }

    void ESeqCanon::visit( const ESeqExpression* n )
    {
        std::cout << "6\n";
        n->stm->Accept( this );
        std::cout << "6accept done\n";
        std::unique_ptr<const IRStatement> canonStm = std::move( prevStm );
        n->expr->Accept( this );
        std::cout << "6 1-move done\n";
        std::unique_ptr<const IRExpression> canonExp = std::move( prevExp );
        std::cout << "6 2-move done\n";

        const ESeqExpression* eseqExp = castToESeqExp( canonExp.get() );
        std::unique_ptr<const IRExpression> resultExp;
        std::cout << "6 start if\n";
        if( eseqExp ) {
            std::cout << "6 1 if-var\n";
            resultExp = std::move( std::make_unique<const ESeqExpression>(
                    std::move( std::make_unique<const SeqStatement>(
                            std::move( canonStm ),
                            eseqExp->GetStm()->GetCopy() ) ),
                    eseqExp->GetExp()->GetCopy() ) );
            std::cout << "6 1 if-var done\n";
        } else {
            std::cout << "6 2 if-var\n";
            resultExp = std::move( std::make_unique<const ESeqExpression>(
                    std::move( canonStm ),
                    std::move( canonExp ) ) );
            std::cout << "6 2 if-var done\n";
        }
        std::cout << "6 all if-var done\n";
        updateLastExp( std::move( resultExp ) );
        std::cout << "6end\n";
    }

    void ESeqCanon::visit( const ExpStatement* n )
    {
        std::cout << "5\n";
        n->exp->Accept( this );
        std::unique_ptr<const IRExpression> canonExp = std::move( prevExp );

        const ESeqExpression* eseqExp = castToESeqExp( canonExp.get() );
        std::unique_ptr<const IRStatement> resultStm;
        if( eseqExp ) {
            resultStm = std::move( std::make_unique<const SeqStatement>(
                    eseqExp->GetStm()->GetCopy(),
                    std::move( std::make_unique<const ExpStatement>( eseqExp->GetExp()->GetCopy() ) ) ) );
        } else {
            resultStm = std::move( std::make_unique<const ExpStatement>( std::move( canonExp ) ) );
        }

        updateLastStm( std::move( resultStm ) );
        std::cout << "5end\n";
    }

    void ESeqCanon::visit( const CJumpStatement* n )
    {
        std::cout << "4\n";
        n->left->Accept( this );
        std::unique_ptr<const IRExpression> canonLeft = std::move( prevExp );
        n->right->Accept( this );
        std::unique_ptr<const IRExpression> canonRight = std::move( prevExp );

        const ESeqExpression* eseqLeft = castToESeqExp( canonLeft.get() );
        const ESeqExpression* eseqRight = castToESeqExp( canonRight.get() );

        std::unique_ptr<const IRStatement> resultStm;

        if( eseqLeft ) {
            resultStm = std::move( std::make_unique<const CJumpStatement>(
                    n->rel,
                    eseqLeft->GetExp()->GetCopy(),
                    std::move( canonRight ),
                    n->if_left,
                    n->if_right ) );
            if( eseqRight ) {
                resultStm = std::move( canonizeStmSubtree( std::move( resultStm ) ) );
            }

            resultStm = std::move( std::make_unique<const SeqStatement>(
                    eseqLeft->GetStm()->GetCopy(),
                    std::move( resultStm ) ) );
        } else if( eseqRight ) {
            if( areCommuting( eseqRight->GetStm(), canonLeft.get() ) ) {
                resultStm = std::move( std::make_unique<const SeqStatement>(
                        eseqRight->GetStm()->GetCopy(),
                        std::move( std::make_unique<const CJumpStatement>(
                                n->rel,
                                std::move( canonLeft ),
                                eseqRight->GetExp()->GetCopy(),
                                n->if_left,
                                n->if_right ) ) ) );
            } else {
                Temp temp;
                resultStm = std::move( std::make_unique<const SeqStatement>(
                        std::move( std::make_unique<const MoveStatement>(
                                std::move( std::make_unique<const TempExpression>( temp ) ),
                                std::move( canonLeft ) ) ),
                        std::move( std::make_unique<const SeqStatement>(
                                eseqRight->GetStm()->GetCopy(),
                                std::move( std::make_unique<const CJumpStatement>(
                                        n->rel,
                                        std::move( std::make_unique<const TempExpression>( temp ) ),
                                        eseqRight->GetExp()->GetCopy(),
                                        n->if_left,
                                        n->if_right ) ) ) ) ) );
            }
        } else {
            resultStm = std::move( std::make_unique<const CJumpStatement>(
                    n->rel,
                    std::move( canonLeft ),
                    std::move( canonRight ),
                    n->if_left,
                    n->if_right ) );
        }

        updateLastStm( std::move( resultStm ) );
        std::cout << "4end\n";
    }

    void ESeqCanon::visit( const JumpStatement* n )
    {
        std::cout << "11\n";
        updateLastStm( n->GetCopy() );
    }

    void ESeqCanon::visit( const LabelStatement* n )
    {
        std::cout << "10\n";
        updateLastStm( n->GetCopy() );
    }

    void ESeqCanon::visit( const MoveStatement* n )
    {
        std::cout << "3\n";
        n->dst->Accept( this );
        std::unique_ptr<const IRExpression> canonDest = std::move( prevExp );
        n->src->Accept( this );
        std::unique_ptr<const IRExpression> canonSrc = std::move( prevExp );

        const ESeqExpression* eseqDest = castToESeqExp( canonDest.get() );
        const ESeqExpression* eseqSrc = castToESeqExp( canonSrc.get() );

        std::unique_ptr<const IRStatement> resultStm;
        if( eseqDest ) {
            std::cout << "3 eseq_dest exist\n";
            resultStm = std::move( std::make_unique<const MoveStatement>(
                    eseqDest->GetExp()->GetCopy(),
                    std::move( canonSrc ) ) );
            if( eseqSrc ) {
                resultStm = std::move( canonizeStmSubtree( std::move( resultStm ) ) );
            }
            resultStm = std::move( std::make_unique<const SeqStatement>(
                    eseqDest->GetStm()->GetCopy(),
                    std::move( resultStm ) ) );
        } else if( eseqSrc ) {
            std::cout << "3 eseq_dest NOT exist, eseqSrc exist.\n";
            if( areCommuting( eseqSrc->GetStm(), canonDest.get() ) ) {
                std::cout << "3 commuting\n";
                resultStm = std::move( std::make_unique<const SeqStatement>(
                        eseqSrc->GetStm()->GetCopy(),
                        std::move( std::make_unique<const MoveStatement>(
                                std::move( canonDest ),
                                eseqSrc->GetExp()->GetCopy() ) ) ) );
            } else {
                std::cout << "3 NOT commuting\n";
                Temp temp;
                resultStm = std::move( std::make_unique<const SeqStatement>(
                        std::move( std::make_unique<const SeqStatement>(
                                eseqSrc->GetStm()->GetCopy(),
                                std::move( std::make_unique<const MoveStatement>(
                                        std::move( std::make_unique<const TempExpression>( temp ) ),
                                        eseqSrc->GetExp()->GetCopy() ) ) ) ),
                        std::move( std::make_unique<const MoveStatement>(
                                std::move( canonDest ),
                                std::move( std::make_unique<const TempExpression>( temp ) ) ) ) ) );
            }
        } else {
            std::cout << "3 eseq_dest NOT exist, eseqSrc NOT exist\n";
            resultStm = std::move( std::make_unique<const MoveStatement>(
                    MoveStatement(
                            std::move( canonDest ),
                            std::move( canonSrc ) ) ) );
        }

        updateLastStm( std::move( resultStm ) );
        std::cout << "3end\n";
    }

    void ESeqCanon::visit( const SeqStatement* n )
    {
        std::cout << "2\n";
        n->left->Accept( this );
        std::unique_ptr<const IRStatement> canonLeft = std::move( prevStm );
        n->right->Accept( this );
        std::unique_ptr<const IRStatement> canonRight = std::move( prevStm );

        updateLastStm( std::move( std::make_unique<const SeqStatement>(
                std::move( canonLeft ),
                std::move( canonRight ) ) ) );
        std::cout << "2end\n";
    }

    void ESeqCanon::visit( const IRExpList* expList )
    {
        std::cout << "1\n";
        std::unique_ptr<IRExpList> newExpList( new IRExpList );
        for( auto& expression : expList->list ) {
            expression->Accept( this );
            newExpList->Add( prevExp.release() );
        }

        updateLastExpList( std::move( newExpList ) );
        std::cout << "1end\n";
    }

//    void ESeqCanon::visit( const CStmList* stmList )
//    {
//        assert( false );
//    }

}
