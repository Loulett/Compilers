#include "Expression.h"
#include "../Visitor.h"
#include <iostream>

AndExpression::AndExpression(IExpression* expr1, IExpression* expr2) {
	if (expr1 == nullptr || expr2 == nullptr) {
		std::cout << "Expression is null.\n";
	}

	this->expr1 = std::unique_ptr<IExpression>(expr1);
	this->expr2 = std::unique_ptr<IExpression>(expr2);
}

void AndExpression::Accept(Visitor* v) const
{
	v->visit(this);
}


LessExpression::LessExpression(IExpression* expr1, IExpression* expr2) {
	if (expr1 == nullptr || expr2 == nullptr) {
		std::cout << "Expression is null.\n";
	}

	this->expr1 = std::unique_ptr<IExpression>(expr1);
	this->expr2 = std::unique_ptr<IExpression>(expr2);
}

void LessExpression::Accept(Visitor* v) const
{
	v->visit(this);
}

PlusExpression::PlusExpression(IExpression* expr1, IExpression* expr2) {
	if (expr1 == nullptr || expr2 == nullptr) {
		std::cout << "Expression is null.\n";
	}

	this->expr1 = std::unique_ptr<IExpression>(expr1);
	this->expr2 = std::unique_ptr<IExpression>(expr2);
}

void PlusExpression::Accept(Visitor* v) const
{
	v->visit(this);
}

MinusExpression::MinusExpression(IExpression* expr1, IExpression* expr2) {
	if (expr1 == nullptr || expr2 == nullptr) {
		std::cout << "Expression is null.\n";
	}

	this->expr1 = std::unique_ptr<IExpression>(expr1);
	this->expr2 = std::unique_ptr<IExpression>(expr2);
}

void MinusExpression::Accept(Visitor* v) const
{
	v->visit(this);
}

MultExpression::MultExpression(IExpression* expr1, IExpression* expr2) {
	if (expr1 == nullptr || expr2 == nullptr) {
		std::cout << "Expression is null.\n";
	}

	this->expr1 = std::unique_ptr<IExpression>(expr1);
	this->expr2 = std::unique_ptr<IExpression>(expr2);
}

void MultExpression::Accept(Visitor* v) const
{
	v->visit(this);
}

RemainExpression::RemainExpression(IExpression* expr1, IExpression* expr2) {
	if (expr1 == nullptr || expr2 == nullptr) {
		std::cout << "Expression is null.\n";
	}

	this->expr1 = std::unique_ptr<IExpression>(expr1);
	this->expr2 = std::unique_ptr<IExpression>(expr2);
}

void RemainExpression::Accept(Visitor* v) const
{
	v->visit(this);
}

OrExpression::OrExpression(IExpression* expr1, IExpression* expr2) {
	if (expr1 == nullptr || expr2 == nullptr) {
		std::cout << "Expression is null.\n";
	}

	this->expr1 = std::unique_ptr<IExpression>(expr1);
	this->expr2 = std::unique_ptr<IExpression>(expr2);
}

void OrExpression::Accept(Visitor* v) const
{
	v->visit(this);
}

ArrayExpression::ArrayExpression(IExpression* expr1, IExpression* expr2) {
	if (expr1 == nullptr || expr2 == nullptr) {
		std::cout << "Expression is null.\n";
	}

	this->expr1 = std::unique_ptr<IExpression>(expr1);
	this->expr2 = std::unique_ptr<IExpression>(expr2);
}

void ArrayExpression::Accept(Visitor* v) const
{
	v->visit(this);
}

LengthExpression::LengthExpression(IExpression* expr) {
	if (expr == nullptr) {
		std::cout << "Expression is null.\n";
	}

	this->expr = std::unique_ptr<IExpression>(expr);
}

void LengthExpression::Accept(Visitor* v) const
{
	v->visit(this);
}

MethodExpression::MethodExpression(IExpression* class_name, IIdentifier* method, std::vector<std::unique_ptr<IExpression>>* params) {
	if (class_name == nullptr || method == nullptr || params == nullptr) {
		std::cout << "While initializing MethodExpression, one of params is nullptr.\n";
	}

	this->class_name = std::unique_ptr<IExpression>(class_name);
	this->method = std::unique_ptr<IIdentifier>(method);
	this->params = std::unique_ptr<std::vector<std::unique_ptr<IExpression>>>(params);
}

void MethodExpression::Accept(Visitor* v) const
{
	v->visit(this);
}

Integer::Integer(int num): num(num) {}

void Integer::Accept(Visitor* v) const
{
	v->visit(this);
}

Bool::Bool(bool b): b(b) {}

void Bool::Accept(Visitor* v) const
{
	v->visit(this);
}

IdentExpression::IdentExpression(IIdentifier* ident) {
	if (ident == nullptr) {
		std::cout << "While initializing IdentExpression, one of params is nullptr.\n";
	}
	this->ident = std::unique_ptr<IIdentifier>(ident);
}

void IdentExpression::Accept(Visitor* v) const
{
	v->visit(this);
}

NewArrExpression::NewArrExpression(IExpression* expr) {
	if (expr == nullptr) {
		std::cout << "While initializing NewArrExpression, one of params is nullptr.\n";
	}
	this->expr = std::unique_ptr<IExpression>(expr);
}

void NewArrExpression::Accept(Visitor* v) const
{
	v->visit(this);
}

NewExpression::NewExpression(IIdentifier* ident) {
	if (ident == nullptr) {
		std::cout << "While initializing NewExpression, one of params is nullptr.\n";
	}
	this->ident = std::unique_ptr<IIdentifier>(ident);
}

void NewExpression::Accept(Visitor* v) const
{
	v->visit(this);
}

NotExpression::NotExpression(IExpression* expr) {
	if(expr == nullptr) {
		std::cout << "While initializing NotExpression, one of params is nullptr.\n";
	}
	this->expr = std::unique_ptr<IExpression>(expr);
}
void NotExpression::Accept(Visitor* v) const
{
	v->visit(this);
}

Expression::Expression(IExpression* expr) {
	if (expr == nullptr) {
		std::cout << "While initializing Expression, one of params is nullptr.\n";
	}
	this->expr = std::unique_ptr<IExpression>(expr);
}

void Expression::Accept(Visitor* v) const
{
	v->visit(this);
}

This::This()  {}
void This::Accept(Visitor* v) const
{
	v->visit(this);
}
