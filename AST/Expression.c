#include "Expression.h"
#include "../Visitor.c"

AndExpression::AndExpression(IExpression* expr1, IExpression* expr2):
	expr1(expr1), expr2(expr2) {}


void AndExpression::Accept(IVisitor* v) const
{
	v->visit(this);
}


LessExpression::LessExpression(IExpression* expr1, IExpression* expr2):
	expr1(expr1), expr2(expr2) {}
void LessExpression::Accept(IVisitor* v) const
{
	v->visit(this);
}

PlusExpression::PlusExpression(IExpression* expr1, IExpression* expr2):
	expr1(expr1), expr2(expr2) {}
void PlusExpression::Accept(IVisitor* v) const
{
	v->visit(this);
}

MinusExpression::MinusExpression(IExpression* expr1, IExpression* expr2):
	expr1(expr1), expr2(expr2) {}
void MinusExpression::Accept(IVisitor* v) const
{
	v->visit(this);
}

MultExpression::MultExpression(IExpression* expr1, IExpression* expr2):
	expr1(expr1), expr2(expr2) {}
void MultExpression::Accept(IVisitor* v) const
{
	v->visit(this);
}

RemainExpression::RemainExpression(IExpression* expr1, IExpression* expr2):
	expr1(expr1), expr2(expr2) {}
void RemainExpression::Accept(IVisitor* v) const
{
	v->visit(this);
}

OrExpression::OrExpression(IExpression* expr1, IExpression* expr2):
	expr1(expr1), expr2(expr2) {}
void OrExpression::Accept(IVisitor* v) const
{
	v->visit(this);
}

ArrayExpression::ArrayExpression(IExpression* expr1, IExpression* expr2):
	expr1(expr1), expr2(expr2) {}
void ArrayExpression::Accept(IVisitor* v) const
{
	v->visit(this);
}

LengthExpression::LengthExpression(IExpression* expr):
	expr(expr) {}
void LengthExpression::Accept(IVisitor* v) const
{
	v->visit(this);
}

MethodExpression::MethodExpression(IExpression* class_name, IIdentifier* method, std::vector<IExpression*>* params):
	class_name(class_name), method(method), params(params) {}

Integer::Integer(int num): num(num) {}
void Integer::Accept(IVisitor* v) const
{
	v->visit(this);
}

Bool::Bool(bool b): b(b) {}
void Bool::Accept(IVisitor* v) const
{
	v->visit(this);
}

IdentExpression::IdentExpression(IIdentifier* ident):
	ident(ident) {}
void IdentExpression::Accept(IVisitor* v) const
{
	v->visit(this);
}

NewArrExpression::NewArrExpression(IExpression* expr):
	expr(expr) {}
void NewArrExpression::Accept(IVisitor* v) const
{
	v->visit(this);
}

NewExpression::NewExpression(IIdentifier* ident):
	ident(ident) {}
void NewExpression::Accept(IVisitor* v) const
{
	v->visit(this);
}

NotExpression::NotExpression(IExpression* expr):
	expr(expr) {}
void NotExpression::Accept(IVisitor* v) const
{
	v->visit(this);
}

Expression::Expression(IExpression* expr):
	expr(expr) {}
void Expression::Accept(IVisitor* v) const
{
	v->visit(this);
}

