#pragma once
#include "INode.h"
#include <vector>
#include <memory>

class AndExpression: public IExpression {
 public:
 	AndExpression(IExpression* expr1, IExpression* expr2);

 	void Accept(Visitor* v) const;

 public:
 	std::unique_ptr<IExpression> expr1;
 	std::unique_ptr<IExpression> expr2;
};

class LessExpression: public IExpression {
 public:
 	LessExpression(IExpression* expr1, IExpression* expr2);
 	void Accept(Visitor* v) const;
 public:
 	std::unique_ptr<IExpression> expr1;
 	std::unique_ptr<IExpression> expr2;
};

class PlusExpression: public IExpression {
 public:
 	void Accept(Visitor* v) const;
	PlusExpression(IExpression* expr1, IExpression* expr2);
 public:
 	std::unique_ptr<IExpression> expr1;
 	std::unique_ptr<IExpression> expr2;
};

class MinusExpression: public IExpression {
 public:
	MinusExpression(IExpression* expr1, IExpression* expr2);
 	void Accept(Visitor* v) const;
 public:
 	std::unique_ptr<IExpression> expr1;
 	std::unique_ptr<IExpression> expr2;
};

class MultExpression: public IExpression {
 public:
 	MultExpression(IExpression* expr1, IExpression* expr2);
	void Accept(Visitor* v) const;

 public:
 	std::unique_ptr<IExpression> expr1;
 	std::unique_ptr<IExpression> expr2;
};

class RemainExpression: public IExpression {
 public:
 	RemainExpression(IExpression* expr1, IExpression* expr2);
	void Accept(Visitor* v) const;
 public:
 	std::unique_ptr<IExpression> expr1;
 	std::unique_ptr<IExpression> expr2;
};

class OrExpression: public IExpression {
 public:
 	OrExpression(IExpression* expr1, IExpression* expr2);
	void Accept(Visitor* v) const;
 public:
 	std::unique_ptr<IExpression> expr1;
 	std::unique_ptr<IExpression> expr2;
};


class ArrayExpression: public IExpression {
 public:
 	ArrayExpression(IExpression* expr1, IExpression* expr2);
	void Accept(Visitor* v) const;
 public:
 	std::unique_ptr<IExpression> expr1;
 	std::unique_ptr<IExpression> expr2;
};

class LengthExpression: public IExpression {
 public:
 	LengthExpression(IExpression* expr);
	void Accept(Visitor* v) const;
 public:
 	std::unique_ptr<IExpression> expr;
};

class MethodExpression: public IExpression {
 public:
 	MethodExpression(IExpression* class_name, IIdentifier* method, std::vector<std::unique_ptr<IExpression>>* params);
	void Accept(Visitor* v) const;
 public:
 	std::unique_ptr<IExpression> class_name;
 	std::unique_ptr<IIdentifier> method;
 	std::unique_ptr<std::vector<std::unique_ptr<IExpression>>> params;
};

class Integer: public IExpression {
 public:
 	Integer(int num);
	void Accept(Visitor* v) const;
 public:
 	int num;
};

class Bool: public IExpression {
 public:
 	Bool(bool b);

	void Accept(Visitor* v) const;

 public:
 	bool b;
};

class IdentExpression: public IExpression {
public:
	IdentExpression(IIdentifier* ident);

	void Accept(Visitor* v) const;

public:
	std::unique_ptr<IIdentifier> ident;
};

class This: public IExpression {
public:
	This();
	void Accept(Visitor* v) const;
};

class NewArrExpression: public IExpression {
 public:
 	NewArrExpression(IExpression* expr);

	void Accept(Visitor* v) const;

 public:
 	std::unique_ptr<IExpression> expr;
};

class NewExpression: public IExpression {
 public:
 	NewExpression(IIdentifier* ident);

	void Accept(Visitor* v) const;

 public:
 	std::unique_ptr<IIdentifier> ident;
};

class NotExpression: public IExpression {
 public:
 	NotExpression(IExpression* expr);

	void Accept(Visitor* v) const;

 public:
 	std::unique_ptr<IExpression> expr;
};

class Expression: public IExpression {
public:
	Expression(IExpression* expr);

	void Accept(Visitor* v) const;

public:
	std::unique_ptr<IExpression> expr;
};
