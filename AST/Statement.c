#include "Statement.h"
#include "../Visitor.h"

Statement::Statement(std::vector<IStatement*>* statements): statements(statements) {}
void Statement::Accept(Visitor* v) const
{
	v->visit(this);
}


IfStatement::IfStatement(IExpression* clause, IStatement* true_statement, IStatement* false_statement):
	clause(clause), true_statement(true_statement), false_statement(false_statement) {}
void IfStatement::Accept(Visitor* v) const
{
	v->visit(this);
}

WhileStatement::WhileStatement(IExpression* clause, IStatement* body):
	clause(clause), body(body) {}
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
