#pragma once
#include "INode.h"
#include <vector>

class Statement:public IStatement{
public:
 	Statement(std::vector<IStatement*>* statements);
  void Accept(Visitor* v) const;
private:
 	std::vector<IStatement*>* statements;
};

class IfStatement: public IStatement {
 public:
 	IfStatement(IExpression* clause, IStatement* true_statement, IStatement* false_statement);
    void Accept(Visitor* v) const;

 private:
 	IExpression* clause;
 	IStatement* true_statement;
 	IStatement* false_statement;
};

class WhileStatement: public IStatement {
 public:
 	WhileStatement(IExpression* clause, IStatement* body);
    void Accept(Visitor* v) const;
 private:
 	IExpression* clause;
 	IStatement* body;
};

class PrintStatement: public IStatement {
 public:
 	PrintStatement(IExpression* print);
    void Accept(Visitor* v) const;
 private:
 	IExpression* print;
};

class AssignmentStatement: public IStatement {
 public:
	AssignmentStatement(IIdentifier* var, IExpression* expr);
    void Accept(Visitor* v) const;
 private:
 	IIdentifier* var;
 	IExpression* expr;
};

class ArrAssignmentStatement: public IStatement {
 public:
 	ArrAssignmentStatement(IIdentifier* var, IExpression* num, IExpression* expr);
    void Accept(Visitor* v) const;
 private:
 	IIdentifier* var;
 	IExpression* num;
 	IExpression* expr;
};