// #include "../SymbolTable/Symbol.h"
#pragma once

#include "IRStatement.h"
#include "IRExpression.h"
#include <vector>
#include <string>
#include <memory>

class MoveStatement : public IRStatement {
public:
    MoveStatement(IRExpression* dst, IRExpression* src);

    MoveStatement( std::unique_ptr<const IRExpression> dst, std::unique_ptr<const IRExpression> src ) :
    dst( std::move( dst ) ), src( std::move( src ) )
    {}  // mb move to .cpp


    void Accept(IRVisitor* v) const override;

    std::unique_ptr<const IRStatement> GetCopy() const override;

    std::unique_ptr<const IRExpression> dst;
    std::unique_ptr<const IRExpression> src;
};

class ExpStatement : public IRStatement {
public:
    //mb тут explicit
    explicit ExpStatement( std::unique_ptr<const IRExpression> exp ) :
            exp( std::move( exp ) )
    {}  // mb move to .cpp

    explicit ExpStatement(IRExpression* exp);




    void Accept(IRVisitor* v) const override;

    std::unique_ptr<const IRStatement> GetCopy() const override;

    std::unique_ptr<const IRExpression> exp;
};

class JumpStatement : public IRStatement {
public:
    explicit JumpStatement(const std::string& label_) : label( label_ ) {}
    void Accept(IRVisitor* v) const override;

    std::unique_ptr<const IRStatement> GetCopy() const override;

    const std::string label;
};

class CJumpStatement : public IRStatement {
public:
    enum Relation { LESS, NEQ, EQ };

    CJumpStatement(CJumpStatement::Relation rel, IRExpression* left, IRExpression* right,
                   std::string& if_left, std::string& if_right);


    CJumpStatement(CJumpStatement::Relation rel, std::unique_ptr<const IRExpression> left,
            std::unique_ptr<const IRExpression> right, const std::string& if_left, const std::string& if_right);

    void Accept(IRVisitor* v) const override;

    std::unique_ptr<const IRStatement> GetCopy() const override;

    CJumpStatement::Relation rel;
    std::unique_ptr<const IRExpression> left;
    std::unique_ptr<const IRExpression> right;
    const std::string if_left;
    const std::string if_right;
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

    std::unique_ptr<const IRStatement> left;
    std::unique_ptr<const IRStatement> right;
};

class LabelStatement : public IRStatement {
public:
//    LabelStatement(std::string& label);
    explicit LabelStatement(const std::string& label) : label( label ) {}
    void Accept(IRVisitor* v) const override;

    const std::string& GetLabel() const;


    std::unique_ptr<const IRStatement> GetCopy() const override;
    const std::string label;
};
