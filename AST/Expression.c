#include "Expression.h"

AndExpression::AndExpression(IExpression* expr1, IExpression* expr2):
	expr1(expr1), expr2(expr2) {}

LessExpression::LessExpression(IExpression* expr1, IExpression* expr2):
	expr1(expr1), expr2(expr2) {}

PlusExpression::PlusExpression(IExpression* expr1, IExpression* expr2):
	expr1(expr1), expr2(expr2) {}

MinusExpression::MinusExpression(IExpression* expr1, IExpression* expr2):
	expr1(expr1), expr2(expr2) {}

MultExpression::MultExpression(IExpression* expr1, IExpression* expr2):
	expr1(expr1), expr2(expr2) {}

RemainExpression::RemainExpression(IExpression* expr1, IExpression* expr2):
	expr1(expr1), expr2(expr2) {}

OrExpression::OrExpression(IExpression* expr1, IExpression* expr2):
	expr1(expr1), expr2(expr2) {}

ArrayExpression::ArrayExpression(IExpression* expr1, IExpression* expr2):
	expr1(expr1), expr2(expr2) {}

LengthExpression::LengthExpression(IExpression* expr):
	expr(expr) {}

Integer::Integer(int num): num(num) {}

Bool::Bool(bool b): b(b) {}

IdentExpression::IdentExpression(IIdentifier* ident):
	ident(ident) {}

NewArrExpression::NewArrExpression(IExpression* expr):
	expr(expr) {}

NewExpression::NewExpression(IIdentifier* ident):
	ident(ident) {}

NotExpression::NotExpression(IExpression* expr):
	expr(expr) {}

Expression::Expression(IExpression* expr):
	expr(expr) {}

int main() {return 0;}

