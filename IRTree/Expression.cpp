#include "Expression.h"
#include "IRVisitor.h"

IRExpList::IRExpList(IRExpression *exp) {
    Add(exp);
}

void IRExpList::Add(IRExpression *exp) {
    list.push_back(exp);
}

std::vector<IRExpression *> IRExpList::Get() {
    return list;
}

ConstExpression::ConstExpression(int val) : value(val) {}

void ConstExpression::Accept(IRVisitor *v) const {
    v->visit(this);
}

NameExpression::NameExpression(std::string &name) : name(name) {}

void NameExpression::Accept(IRVisitor *v) const {
    v->visit(this);
}

TempExpression::TempExpression(std::string &name) : name(name) {}

void TempExpression::Accept(IRVisitor *v) const {
    v->visit(this);
}

BinOpExpression::BinOpExpression(BinOp binop, IRExpression *left, IRExpression *right) : binop(binop), left(left),
                                                                                         right(right) {}

void BinOpExpression::Accept(IRVisitor *v) const {
    v->visit(this);
}

MemExpression::MemExpression(IRExpression *expr) : expr(expr) {}

void MemExpression::Accept(IRVisitor *v) const {
    v->visit(this);
}

CallExpression::CallExpression(IRExpression *func, IRExpList *args) : func(func), args(args) {}

void CallExpression::Accept(IRVisitor *v) const {
    v->visit(this);
}

ESeqExpression::ESeqExpression(IRStatement *stm, IRExpression *expr) : stm(stm), expr(expr) {}

void ESeqExpression::Accept(IRVisitor *v) const {
    v->visit(this);
}
