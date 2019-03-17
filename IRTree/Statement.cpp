#include "Statement.h"

MoveStatement::MoveStatement(IRExpression* dst, IRExpression* src): dst(dst), src(src) {}

ExpStatement::ExpStatement(IRExpression* exp): exp(exp) {}

JumpStatement::JumpStatement(std::string& label): label(label) {}

CJumpStatement::CJumpStatement(int rel, IRExpression* left, IRExpression* right, std::string& if_left, std::string& if_right):
    rel(rel), left(left), right(right), if_left(if_left), if_right(if_right) {}

SeqStatement::SeqStatement(IRStatement* left, IRStatement* right): left(left), right(right) {}

LabelStatement::LabelStatement(std::string& label): label(label) {}
