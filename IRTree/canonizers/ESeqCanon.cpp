#include "ESeqCanon.h"
#include <cassert>
#include <iostream>


namespace IRT
{

    std::unique_ptr<const IRStatement> ESeqCanon::CanonicalTree()
    {
        return std::move( CanonicalStmTree() );
    }

    std::unique_ptr<const IRStatement> ESeqCanon::CanonicalStmTree()
    {
        return std::move( prevStm );
    }

    std::unique_ptr<const IRExpression> ESeqCanon::CanonicalExpTree()
    {
        return std::move( prevExp );
    }

    void ESeqCanon::updateLastExp( const IRExpression* newLastExp )
    {
        prevExp = std::move( std::unique_ptr<const IRExpression>( newLastExp ) );
    }

    void ESeqCanon::updateLastExp( std::unique_ptr<const IRExpression> newLastExp )
    {
        prevExp = std::move( newLastExp );
    }

    void ESeqCanon::updateLastExpList( std::unique_ptr<const IRExpList> newLastExpList )
    {
        prevExpList = std::move( newLastExpList );
    }

    void ESeqCanon::updateLastStm( std::unique_ptr<const IRStatement> newLastStm )
    {
        prevStm = std::move( newLastStm );
    }

    std::unique_ptr<const IRExpression> ESeqCanon::canonizeExpSubtree( std::unique_ptr<const IRExpression> exp ) const
    {
        ESeqCanon visitor;
        exp->Accept( &visitor );
        return visitor.CanonicalExpTree();
    }

    std::unique_ptr<const IRStatement> ESeqCanon::canonizeStmSubtree( std::unique_ptr<const IRStatement> stm ) const
    {
        ESeqCanon visitor;
        stm->Accept( &visitor );
        return visitor.CanonicalStmTree();
    }

    bool ESeqCanon::areCommuting( const IRStatement* stm, const IRExpression* exp )
    {
        assert( stm != nullptr && exp != nullptr );
        auto expStm = dynamic_cast<const CExpStm*>( stm );
        bool isStmEmpty = expStm != nullptr &&
                          dynamic_cast<const CConstExp*>( expStm->GetExp() ) != nullptr;
        return isStmEmpty ||
               dynamic_cast<const CConstExp*>( exp ) != nullptr ||
               dynamic_cast<const CNameExp*>( exp ) != nullptr;
    }

    const CESeqExp* ESeqCanon::castToESeqExp( const IRExpression* exp )
    {
        return dynamic_cast<const CESeqExp*>( exp );
    }

    void ESeqCanon::Visit( const CConstExp* n )
    {
        updateLastExp( std::make_unique<const CConstExp>( n->GetValue() ) );
    }

    void ESeqCanon::Visit( const CNameExp* n )
    {
        updateLastExp( std::make_unique<const CNameExp>( n->GetLabel() ) );
    }

    void ESeqCanon::Visit( const CTempExp* n )
    {
        static int numEntries = 0;
        std::cout << numEntries << std::endl;
        updateLastExp( std::move( std::make_unique<const CTempExp>( n->GetTemp() ) ) );
        numEntries++;
    }

    void ESeqCanon::Visit( const CBinaryExp* n )
    {
        n->GetLeft()->Accept( this );
        std::unique_ptr<const IRExpression> canonLeft = std::move( prevExp );
        n->GetRight()->Accept( this );
        std::unique_ptr<const IRExpression> canonRight = std::move( prevExp );

        const CESeqExp* eseqLeft = castToESeqExp( canonLeft.get() );
        const CESeqExp* eseqRight = castToESeqExp( canonRight.get() );

        std::unique_ptr<const IRExpression> resultExp;
        if( eseqLeft ) {
            resultExp = std::move( std::make_unique<const CESeqExp>(
                    eseqLeft->GetStm()->GetCopy(),
                    std::move( std::make_unique<const CBinaryExp>(
                            n->GetType(),
                            eseqLeft->GetExp()->GetCopy(),
                            std::move( canonRight ) ) ) ) );
            if( eseqRight ) {
                resultExp = canonizeExpSubtree( std::move( resultExp ) );
            }
        } else if( eseqRight ) {
            if( areCommuting( eseqRight->GetStm(), canonLeft.get() ) ) {
                resultExp = std::move( std::make_unique<const CESeqExp>(
                        eseqRight->GetStm()->GetCopy(),
                        std::move( std::make_unique<const CBinaryExp>(
                                n->GetType(),
                                std::move( canonLeft ),
                                eseqRight->GetExp()->GetCopy() ) ) ) );
            } else {
                CTemp temp;
                resultExp = std::move( std::make_unique<const CESeqExp>(
                        std::move( std::make_unique<const CMoveStm>(
                                std::move( std::make_unique<const CTempExp>( temp ) ),
                                std::move( canonLeft ) ) ),
                        std::move( std::make_unique<const CESeqExp>(
                                eseqRight->GetStm()->GetCopy(),
                                std::move( std::make_unique<const CBinaryExp>(
                                        n->GetType(),
                                        std::move( std::make_unique<const CTempExp>( temp ) ),
                                        eseqRight->GetExp()->GetCopy() ) ) ) ) ) );
                resultExp = std::move( canonizeExpSubtree( std::move( resultExp ) ) );
            }
        } else {
            resultExp = std::move( std::make_unique<const CBinaryExp>(
                    n->GetType(),
                    canonLeft.release(),
                    canonRight.release() ) );
        }

        updateLastExp( resultExp.release() );
    }

    void ESeqCanon::Visit( const CMemoryExp* n )
    {
        n->GetMem()->Accept( this );
        std::unique_ptr<const IRExpression> canonAddr = std::move( prevExp );

        const CESeqExp* eseqAddr = castToESeqExp( canonAddr.get() );
        std::unique_ptr<const IRExpression> resultExp = nullptr;
        if( eseqAddr ) {
            resultExp = std::move( std::make_unique<const CESeqExp>(
                    eseqAddr->GetStm()->GetCopy(),
                    std::move( std::make_unique<CMemoryExp>( eseqAddr->GetExp()->GetCopy() ) ) ) );
        } else {
            resultExp = std::move( std::make_unique<const CMemoryExp>( canonAddr.release() ) );
        }
        updateLastExp( resultExp.release() );
    }

    void ESeqCanon::Visit( const CCallExp* n )
    {
        n->GetFuncExp()->Accept( this );
        std::unique_ptr<const IRExpression> canonFunc = std::move( prevExp );

        n->GetArgs()->Accept( this );
        std::vector<std::unique_ptr<const IRStatement>> newStms;

        std::unique_ptr<IRExpList> newArgs = std::make_unique<IRExpList>();
        std::unique_ptr<const IRExpList> canonArgList = std::move( prevExpList );
        for( auto& canonArg : canonArgList->GetExpressions() ) {
            const CESeqExp* eseqArg = castToESeqExp( canonArg.get() );
            if( eseqArg ) {
                newStms.push_back( eseqArg->GetStm()->GetCopy() );
            }

            CTemp temp;
            newArgs->Add( new CTempExp( temp ) );

            std::unique_ptr<const IRExpression> moveSrcExp;
            if( eseqArg ) {
                moveSrcExp = eseqArg->GetExp()->GetCopy();
            } else {
                moveSrcExp = canonArg->GetCopy();
            }
            std::unique_ptr<const IRStatement> moveStm = std::move( std::make_unique<const CMoveStm>(
                    std::move( std::make_unique<const CTempExp>( temp ) ),
                    std::move( moveSrcExp ) ) );
            newStms.push_back( std::move( moveStm ) );
        }

        std::unique_ptr<const IRExpression> resultExp;
        if( !newStms.empty() ) {
            std::unique_ptr<const IRStatement> suffStm = std::move( newStms.back() );
            newStms.pop_back();
            for( int i = newStms.size() - 1; i >= 0 ; i-- ) {
                suffStm = std::move( std::make_unique<const CSeqStm>(
                        std::move( newStms[i] ) ,
                        std::move( suffStm )));
            }

            resultExp = std::move( std::make_unique<const CESeqExp>(
                    std::move( suffStm ),
                    std::move( std::make_unique<const CCallExp>(
                            std::move( canonFunc ),
                            std::move( newArgs ) ) ) ) );
        } else {
            resultExp = std::move( std::make_unique<const CCallExp>(
                    std::move( canonFunc ),
                    std::move( canonArgList ) ) );
        }

        updateLastExp( std::move( resultExp ) );

    }

    void ESeqCanon::Visit( const CESeqExp* n )
    {
        n->GetStm()->Accept( this );
        std::unique_ptr<const IRStatement> canonStm = std::move( prevStm );
        n->GetExp()->Accept( this );
        std::unique_ptr<const IRExpression> canonExp = std::move( prevExp );

        const CESeqExp* eseqExp = castToESeqExp( canonExp.get() );
        std::unique_ptr<const IRExpression> resultExp;
        if( eseqExp ) {
            resultExp = std::move( std::make_unique<const CESeqExp>(
                    std::move( std::make_unique<const CSeqStm>(
                            std::move( canonStm ),
                            eseqExp->GetStm()->GetCopy() ) ),
                    eseqExp->GetExp()->GetCopy() ) );
        } else {
            resultExp = std::move( std::make_unique<const CESeqExp>(
                    std::move( canonStm ),
                    std::move( canonExp ) ) );
        }

        updateLastExp( std::move( resultExp ) );

    }

    void ESeqCanon::Visit( const CExpStm* n )
    {

        n->GetExp()->Accept( this );
        std::unique_ptr<const IRExpression> canonExp = std::move( prevExp );

        const CESeqExp* eseqExp = castToESeqExp( canonExp.get() );
        std::unique_ptr<const IRStatement> resultStm;
        if( eseqExp ) {
            resultStm = std::move( std::make_unique<const CSeqStm>(
                    eseqExp->GetStm()->GetCopy(),
                    std::move( std::make_unique<const CExpStm>( eseqExp->GetExp()->GetCopy() ) ) ) );
        } else {
            resultStm = std::move( std::make_unique<const CExpStm>( std::move( canonExp ) ) );
        }

        updateLastStm( std::move( resultStm ) );

    }

    void ESeqCanon::Visit( const CCJumpStm* n )
    {

        n->GetLeft()->Accept( this );
        std::unique_ptr<const IRExpression> canonLeft = std::move( prevExp );
        n->GetRight()->Accept( this );
        std::unique_ptr<const IRExpression> canonRight = std::move( prevExp );

        const CESeqExp* eseqLeft = castToESeqExp( canonLeft.get() );
        const CESeqExp* eseqRight = castToESeqExp( canonRight.get() );

        std::unique_ptr<const IRStatement> resultStm;

        if( eseqLeft ) {
            resultStm = std::move( std::make_unique<const CCJumpStm>(
                    n->GetType(),
                    eseqLeft->GetExp()->GetCopy(),
                    std::move( canonRight ),
                    n->GetTrueLabel(),
                    n->GetFalseLabel() ) );
            if( eseqRight ) {
                resultStm = std::move( canonizeStmSubtree( std::move( resultStm ) ) );
            }

            resultStm = std::move( std::make_unique<const CSeqStm>(
                    eseqLeft->GetStm()->GetCopy(),
                    std::move( resultStm ) ) );
        } else if( eseqRight ) {
            if( areCommuting( eseqRight->GetStm(), canonLeft.get() ) ) {
                resultStm = std::move( std::make_unique<const CSeqStm>(
                        eseqRight->GetStm()->GetCopy(),
                        std::move( std::make_unique<const CCJumpStm>(
                                n->GetType(),
                                std::move( canonLeft ),
                                eseqRight->GetExp()->GetCopy(),
                                n->GetTrueLabel(),
                                n->GetFalseLabel() ) ) ) );
            } else {
                CTemp temp;
                resultStm = std::move( std::make_unique<const CSeqStm>(
                        std::move( std::make_unique<const CMoveStm>(
                                std::move( std::make_unique<const CTempExp>( temp ) ),
                                std::move( canonLeft ) ) ),
                        std::move( std::make_unique<const CSeqStm>(
                                eseqRight->GetStm()->GetCopy(),
                                std::move( std::make_unique<const CCJumpStm>(
                                        n->GetType(),
                                        std::move( std::make_unique<const CTempExp>( temp ) ),
                                        eseqRight->GetExp()->GetCopy(),
                                        n->GetTrueLabel(),
                                        n->GetFalseLabel() ) ) ) ) ) );
            }
        } else {
            resultStm = std::move( std::make_unique<const CCJumpStm>(
                    n->GetType(),
                    std::move( canonLeft ),
                    std::move( canonRight ),
                    n->GetTrueLabel(),
                    n->GetFalseLabel() ) );
        }

        updateLastStm( std::move( resultStm ) );

    }

    void ESeqCanon::Visit( const CJumpStm* n )
    {
        updateLastStm( n->GetCopy() );
    }

    void ESeqCanon::Visit( const CLabelStm* n )
    {
        updateLastStm( n->GetCopy() );
    }

    void ESeqCanon::Visit( const CMoveStm* n )
    {
        n->GetDst()->Accept( this );
        std::unique_ptr<const IRExpression> canonDest = std::move( prevExp );
        n->GetSrc()->Accept( this );
        std::unique_ptr<const IRExpression> canonSrc = std::move( prevExp );

        const CESeqExp* eseqDest = castToESeqExp( canonDest.get() );
        const CESeqExp* eseqSrc = castToESeqExp( canonSrc.get() );

        std::unique_ptr<const IRStatement> resultStm;
        if( eseqDest ) {
            resultStm = std::move( std::make_unique<const CMoveStm>(
                    eseqDest->GetExp()->GetCopy(),
                    std::move( canonSrc ) ) );
            if( eseqSrc ) {
                resultStm = std::move( canonizeStmSubtree( std::move( resultStm ) ) );
            }
            resultStm = std::move( std::make_unique<const CSeqStm>(
                    eseqDest->GetStm()->GetCopy(),
                    std::move( resultStm ) ) );
        } else if( eseqSrc ) {
            if( areCommuting( eseqSrc->GetStm(), canonDest.get() ) ) {
                resultStm = std::move( std::make_unique<const CSeqStm>(
                        eseqSrc->GetStm()->GetCopy(),
                        std::move( std::make_unique<const CMoveStm>(
                                std::move( canonDest ),
                                eseqSrc->GetExp()->GetCopy() ) ) ) );
            } else {
                CTemp temp;
                resultStm = std::move( std::make_unique<const CSeqStm>(
                        std::move( std::make_unique<const CSeqStm>(
                                eseqSrc->GetStm()->GetCopy(),
                                std::move( std::make_unique<const CMoveStm>(
                                        std::move( std::make_unique<const CTempExp>( temp ) ),
                                        eseqSrc->GetExp()->GetCopy() ) ) ) ),
                        std::move( std::make_unique<const CMoveStm>(
                                std::move( canonDest ),
                                std::move( std::make_unique<const CTempExp>( temp ) ) ) ) ) );
            }
        } else {
            resultStm = std::move( std::make_unique<const CMoveStm>(
                    CMoveStm(
                            std::move( canonDest ),
                            std::move( canonSrc ) ) ) );
        }

        updateLastStm( std::move( resultStm ) );

    }

    void ESeqCanon::Visit( const CSeqStm* n )
    {
        n->GetLeft()->Accept( this );
        std::unique_ptr<const IRStatement> canonLeft = std::move( prevStm );
        n->GetRight()->Accept( this );
        std::unique_ptr<const IRStatement> canonRight = std::move( prevStm );

        updateLastStm( std::move( std::make_unique<const CSeqStm>(
                std::move( canonLeft ),
                std::move( canonRight ) ) ) );
    }

    void ESeqCanon::Visit( const IRExpList* expList )
    {
        std::unique_ptr<IRExpList> newExpList( new IRExpList );
        for( auto& expression : expList->GetExpressions() ) {
            expression->Accept( this );
            newExpList->Add( prevExp.release() );
        }

        updateLastExpList( std::move( newExpList ) );
    }

    void ESeqCanon::Visit( const CStmList* stmList )
    {
        assert( false );
    }

}
