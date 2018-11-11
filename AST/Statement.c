#include "Statement.h"

Statement::Statement(std::vector<IStatement*> statements): statements(statements) {}
void Statement::Accept(IVisitor* v) const
{
	v->visit(this);
}


IfStatement::IfStatement(IExpression* clause, IStatement* true_statement, IStatement* false_statement):
	clause(clause), true_statement(true_statement), false_statement(false_statement) {}
void IfStatement::Accept(IVisitor* v) const
{
	v->visit(this);
}

WhileStatement::WhileStatement(IExpression* clause, IStatement* body):
	clause(clause), body(body) {}
void WhileStatement::Accept(IVisitor* v) const
{
	v->visit(this);
}

PrintStatement::PrintStatement(IExpression* print):
	print(print) {}
void PrintStatement::Accept(IVisitor* v) const
{
	v->visit(this);
}

AssignmentStatement::AssignmentStatement(IIdentifier* var, IExpression* expr):
	var(var), expr(expr) {}
void AssignmentStatement::Accept(IVisitor* v) const
{
	v->visit(this);
}

ArrAssignmentStatement::ArrAssignmentStatement(IIdentifier* var, IExpression* num, IExpression* expr):
	var(var), num(num), expr(expr) {}
void ArrAssignmentStatement::Accept(IVisitor* v) const
{
	v->visit(this);
}

int main() {return 0;}