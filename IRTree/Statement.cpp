#include "Statement.h"
#include "IRVisitor.h"

MoveStatement::MoveStatement(IRExpression *dst, IRExpression *src) : dst(dst), src(src) {}

void MoveStatement::Accept(IRVisitor *v) const {
    v->visit(this);
}

ExpStatement::ExpStatement(IRExpression *exp) : exp(exp) {}

void ExpStatement::Accept(IRVisitor *v) const {
    v->visit(this);
}

JumpStatement::JumpStatement(std::string &label) : label(label) {}

void JumpStatement::Accept(IRVisitor *v) const {
    v->visit(this);
}

CJumpStatement::CJumpStatement(CJumpStatement::Relation rel, IRExpression *left, IRExpression *right,
                               std::string &if_left, std::string &if_right) :
        rel(rel), left(left), right(right), if_left(if_left), if_right(if_right) {}

void CJumpStatement::Accept(IRVisitor *v) const {
    v->visit(this);
}

SeqStatement::SeqStatement(IRStatement *left, IRStatement *right) : left(left), right(right) {}

void SeqStatement::Accept(IRVisitor *v) const {
    v->visit(this);
}

LabelStatement::LabelStatement(std::string &label) : label(label) {}

void LabelStatement::Accept(IRVisitor *v) const {
    v->visit(this);
}
