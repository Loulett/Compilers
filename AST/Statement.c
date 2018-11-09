#include "Statement.h"

Statement::Statement(std::vector<IStatement*>* statements): statements(statements) {}

IfStatement::IfStatement(IExpression* clause, IStatement* true_statement, IStatement* false_statement):
	clause(clause), true_statement(true_statement), false_statement(false_statement) {}

WhileStatement::WhileStatement(IExpression* clause, IStatement* body):
	clause(clause), body(body) {}

PrintStatement::PrintStatement(IExpression* print):
	print(print) {}

AssignmentStatement::AssignmentStatement(IIdentifier* var, IExpression* expr):
	var(var), expr(expr) {}

ArrAssignmentStatement::ArrAssignmentStatement(IIdentifier* var, IExpression* num, IExpression* expr):
	var(var), num(num), expr(expr) {}