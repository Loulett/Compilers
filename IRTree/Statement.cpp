#include "Statement.h"

MoveStatement::MoveStatement(IRExpression* dst, IRExpression* src): dst(dst), src(src) {}

ExpStatement::ExpStatement(IRExpression* exp): exp(exp) {}

JumpStatement::JumpStatement(IRExpression* exp): exp(exp) {}

CJumpStatement::CJumpStatement(int rel, IRExpression* left, IRExpression* right, Symbol* if_left, Symbol* if_right):
    rel(rel), left(left), right(right), if_left(if_left), if_right(if_right) {}

SeqStatement::SeqStatement(IRStatement* left, IRStatement* right): left(left), right(right) {}

LabelStatement::LabelStatement(Symbol* label): label(label) {}
