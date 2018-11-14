#include "Statement.h"
#include "../Visitor.h"
#include <iostream>

Statement::Statement(std::vector<std::unique_ptr<IStatement>>* statements) {
	if (statements == nullptr) {
		std::cout << "Statement is nullptr.\n";
	}
	this->statements = std::unique_ptr<std::vector<std::unique_ptr<IStatement>>>(statements);
}

void Statement::Accept(Visitor* v) const
{
	v->visit(this);
}


IfStatement::IfStatement(IExpression* clause, IStatement* true_statement, IStatement* false_statement) {
	if (clause == nullptr || true_statement == nullptr || false_statement == nullptr) {
		std::cout << "Statement is nullptr.\n";
	}
	this->clause = std::unique_ptr<IExpression>(clause);
	this->true_statement = std::unique_ptr<IStatement>(true_statement);
	this->false_statement = std::unique_ptr<IStatement>(false_statement);
}

void IfStatement::Accept(Visitor* v) const
{
	v->visit(this);
}

WhileStatement::WhileStatement(IExpression* clause, IStatement* body) {
	if (clause == nullptr || body == nullptr) {
		std::cout << "Statement is nullptr.\n";
	}
	this->clause = std::unique_ptr<IExpression>(clause);
	this->body = std::unique_ptr<IStatement>(body);
}

void WhileStatement::Accept(Visitor* v) const
{
	v->visit(this);
}

PrintStatement::PrintStatement(IExpression* print):
	print(print) {}
void PrintStatement::Accept(Visitor* v) const
{
	v->visit(this);
}

AssignmentStatement::AssignmentStatement(IIdentifier* var, IExpression* expr):
	var(var), expr(expr) {}
void AssignmentStatement::Accept(Visitor* v) const
{
	v->visit(this);
}

ArrAssignmentStatement::ArrAssignmentStatement(IIdentifier* var, IExpression* num, IExpression* expr):
	var(var), num(num), expr(expr) {}
void ArrAssignmentStatement::Accept(Visitor* v) const
{
	v->visit(this);
}
