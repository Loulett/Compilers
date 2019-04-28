#include "Statement.h"
#include "IRVisitor.h"

// 1
std::unique_ptr<const IRStatement> ExpStatement::GetCopy() const
{
    return std::move(std::make_unique<const ExpStatement>( exp->GetCopy() ) );
}

std::unique_ptr<const IRStatement> JumpStatement::GetCopy() const
{
    return std::move(std::make_unique<const JumpStatement>( label ) );
}

std::unique_ptr<const IRStatement> CJumpStatement::GetCopy() const
{
    return std::move(std::make_unique<const CJumpStatement>( rel, left.get(), right.get(),
                                                   if_left, if_right ) );
}

std::unique_ptr<const IRStatement> SeqStatement::GetCopy() const
{
    return std::move(std::make_unique<const SeqStatement>( left->GetCopy(), right->GetCopy() ) );
}

std::unique_ptr<const IRStatement> LabelStatement::GetCopy() const
{
    return std::move(std::make_unique<const LabelStatement>( label ) );
}

// 2
std::unique_ptr<const IRStatement> MoveStatement::GetCopy() const
{
    return std::move(std::make_unique<const MoveStatement>( dst->GetCopy(), src->GetCopy() ) );
}



CJumpStatement(CJumpStatement::Relation rel, std::unique_ptr<const IRExpression> left,
        std::unique_ptr<const IRExpression> right, std::string& if_left, std::string& if_right) :
        relationType( rel ), leftExp( std::move( left ) ), rightExp( std::move( right ) ),
        if_left( ifTrue ), if_right( ifFalse )
{
}

//end




MoveStatement::MoveStatement(IRExpression *dst, IRExpression *src) : dst(dst), src(src) {
}

void MoveStatement::Accept(IRVisitor *v) const {
    v->visit(this);
}

ExpStatement::ExpStatement(IRExpression *exp) : exp(exp) {
}

void ExpStatement::Accept(IRVisitor *v) const {
    v->visit(this);
}

JumpStatement::JumpStatement(std::string &label) : label(label) {
}

void JumpStatement::Accept(IRVisitor *v) const {
    v->visit(this);
}

CJumpStatement::CJumpStatement(CJumpStatement::Relation rel, IRExpression *left,
                               IRExpression *right, std::string &if_left, std::string &if_right)
    : rel(rel), left(left), right(right), if_left(if_left), if_right(if_right) {
}

void CJumpStatement::Accept(IRVisitor *v) const {
    v->visit(this);
}

SeqStatement::SeqStatement(IRStatement *left, IRStatement *right) : left(left), right(right) {
}

void SeqStatement::Accept(IRVisitor *v) const {
    v->visit(this);
}

LabelStatement::LabelStatement(std::string &label) : label(label) {
}

void LabelStatement::Accept(IRVisitor *v) const {
    v->visit(this);
}
