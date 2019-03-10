#include "Expression.h"

IRExpList::IRExpList(IRExpression* exp) {
    Add(exp);
}

void IRExpList::Add(IRExpression* exp) {
    list.push_back(exp);
}

std::vector<IRExpression*> IRExpList::Get() {
    return list;
}

ConstExpression::ConstExpression(int val): value(val) {}

NameExpression::NameExpression(Symbol* name): name(name) {}

TempExpression::TempExpression(Symbol* name): name(name) {}

BinOpExpression::BinOpExpression(BinOp binop, IRExpression* left, IRExpression* right): binop(binop), left(left), right(right) {}

MemExpression::MemExpression(IRExpression* expr): expr(expr) {}

CallExpression::CallExpression(IRExpression* func, IRExpList* args): func(func), args(args) {}

ESeqExpression::ESeqExpression(IRStatement* stm, IRExpression* expr): stm(stm), expr(expr) {}
