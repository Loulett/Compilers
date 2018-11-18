#pragma once
#include "INode.h"
#include <vector>
#include <memory>

class Statement:public IStatement{
public:
 	Statement(std::vector<std::unique_ptr<IStatement>>* statements);
  void Accept(Visitor* v) const;
public:
 	std::unique_ptr<std::vector<std::unique_ptr<IStatement>>> statements;
};

class IfStatement: public IStatement {
 public:
 	IfStatement(IExpression* clause, IStatement* true_statement, IStatement* false_statement);
    void Accept(Visitor* v) const;

 public:
 	std::unique_ptr<IExpression> clause;
 	std::unique_ptr<IStatement> true_statement;
 	std::unique_ptr<IStatement> false_statement;
};

class WhileStatement: public IStatement {
 public:
 	WhileStatement(IExpression* clause, IStatement* body);
    void Accept(Visitor* v) const;
 public:
 	std::unique_ptr<IExpression> clause;
 	std::unique_ptr<IStatement> body;
};

class PrintStatement: public IStatement {
 public:
 	PrintStatement(IExpression* print);
    void Accept(Visitor* v) const;
 public:
 	std::unique_ptr<IExpression> print;
};

class AssignmentStatement: public IStatement {
 public:
	AssignmentStatement(IIdentifier* var, IExpression* expr);
    void Accept(Visitor* v) const;
 public:
 	IIdentifier* var;
 	IExpression* expr;
};

class ArrAssignmentStatement: public IStatement {
 public:
 	ArrAssignmentStatement(IIdentifier* var, IExpression* num, IExpression* expr);
    void Accept(Visitor* v) const;
 public:
 	IIdentifier* var;
 	IExpression* num;
 	IExpression* expr;
};