// #include "../SymbolTable/Symbol.h"
#pragma once

#include "IRStatement.h"
#include "IRExpression.h"
#include <vector>
#include <string>

class MoveStatement : public IRStatement {
public:
    MoveStatement(IRExpression* dst, IRExpression* src);

    MoveStatement( std::unique_ptr<const IRExpression> dst, std::unique_ptr<const IRExpression> src ) :
    dst( std::move( dst ) ), src( std::move( src ) )
    {}  // mb move to .cpp


    void Accept(IRVisitor* v) const override;

    std::unique_ptr<const IRStatement> GetCopy() const override;

    IRExpression* dst;
    IRExpression* src;
};

class ExpStatement : public IRStatement {
public:
    explicit ExpStatement(IRExpression* exp);

    //mb тут explicit
    explicit ExpStatement( std::unique_ptr<const IRStatement> exp ) :
    exp( std::move( exp ) )
    {}  // mb move to .cpp


    void Accept(IRVisitor* v) const override;

    std::unique_ptr<const IRStatement> GetCopy() const override;

    IRExpression* exp;
};

class JumpStatement : public IRStatement {
public:
    JumpStatement(std::string& label);
    void Accept(IRVisitor* v) const override;

    std::unique_ptr<const IRStatement> GetCopy() const override;

    std::string label;
};

class CJumpStatement : public IRStatement {
public:
    enum Relation { LESS, NEQ, EQ };

    CJumpStatement(CJumpStatement::Relation rel, IRExpression* left, IRExpression* right,
                   std::string& if_left, std::string& if_right);


    CJumpStatement(CJumpStatement::Relation rel, std::unique_ptr<const IRExpression> left,
            std::unique_ptr<const IRExpression> right, std::string& if_left, std::string& if_right);

    void Accept(IRVisitor* v) const override;

    std::unique_ptr<const IRStatement> GetCopy() const override;

    CJumpStatement::Relation rel;
    IRExpression* left;
    IRExpression* right;
    std::string if_left;
    std::string if_right;
};

class SeqStatement : public IRStatement {
public:
    SeqStatement(IRStatement* left, IRStatement* right);

    SeqStatement( std::unique_ptr<const IRStatement> left, std::unique_ptr<const IRStatement> right ) :
    left( std::move( left ) ), right( std::move( right ) )
    {
    }



    void Accept(IRVisitor* v) const override;

    std::unique_ptr<const IRStatement> GetCopy() const override;

    IRStatement* left;
    IRStatement* right;
};

class LabelStatement : public IRStatement {
public:
    LabelStatement(std::string& label);
    void Accept(IRVisitor* v) const override;

    std::unique_ptr<const IRStatement> GetCopy() const override;

    std::string label;
};
