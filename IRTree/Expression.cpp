#include "Expression.h"
#include "IRVisitor.h"

std::unique_ptr<const IRExpList> IRExpList::GetCopy() const
{
    std::unique_ptr<IRExpList> list_output = std::make_unique<IRExpList>();
    for( const auto& expression : list ) {
        list_output->Add( expression->GetCopy().release() );
    }
    return list_output;
}


std::unique_ptr<const IRExpression> ConstExpression::GetCopy() const
{
    return std::move(std::make_unique<ConstExpression>( value ) );
}
std::unique_ptr<const IRExpression> NameExpression::GetCopy() const
{
    return std::move(std::make_unique<NameExpression>( name ) );
}
std::unique_ptr<const IRExpression> TempExpression::GetCopy() const
{
    return std::move(std::make_unique<TempExpression>( name ) );
}
std::unique_ptr<const IRExpression> BinOpExpression::GetCopy() const
{
    return std::move(std::make_unique<BinOpExpression>( binop, left.get(), right.get() ) );
}
std::unique_ptr<const IRExpression> MemExpression::GetCopy() const
{
    return std::move(std::make_unique<MemExpression>( expr->GetCopy().get() ) );
}
std::unique_ptr<const IRExpression> CallExpression::GetCopy() const
{
    return std::move(std::make_unique<CallExpression>( func->GetCopy(), args->GetCopy() ) );
}
std::unique_ptr<const IRExpression> ESeqExpression::GetCopy() const
{
    return std::move(std::make_unique<const ESeqExpression>( stm->GetCopy(), expr->GetCopy() ) );
}













//IRExpList::IRExpList(IRExpression *exp) {
//    Add(exp);
//}

//void IRExpList::Add(IRExpression *exp) {
//    list.push_back(exp);
//}

//std::vector<IRExpression *> IRExpList::Get() {
//    return list;
//}

ConstExpression::ConstExpression(int val) : value(val) {
}

void ConstExpression::Accept(IRVisitor *v) const {
    v->visit(this);
}

NameExpression::NameExpression(std::string &name) : name(name) {
}

void NameExpression::Accept(IRVisitor *v) const {
    v->visit(this);
}

TempExpression::TempExpression(std::string &name) : name(name) {
}

void TempExpression::Accept(IRVisitor *v) const {
    v->visit(this);
}

BinOpExpression::BinOpExpression(BinOp binop, IRExpression *left, IRExpression *right)
    : binop(binop), left(left), right(right) {
}

void BinOpExpression::Accept(IRVisitor *v) const {
    v->visit(this);
}

//MemExpression::MemExpression(IRExpression *expr) : expr(expr) {
//}

void MemExpression::Accept(IRVisitor *v) const {
    v->visit(this);
}

CallExpression::CallExpression(IRExpression *func, IRExpList *args) : func(func), args(args) {
}

void CallExpression::Accept(IRVisitor *v) const {
    v->visit(this);
}

ESeqExpression::ESeqExpression(IRStatement *stm, IRExpression *expr) : stm(stm), expr(expr) {
}

void ESeqExpression::Accept(IRVisitor *v) const {
    v->visit(this);
}
