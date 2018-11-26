#pragma once


struct Visitor;

class INode {
 public:
    virtual void Accept(Visitor* v) const = 0;
};

class IGoal: public INode {
 public:
 	virtual ~IGoal() = default;
};

class IMainClass: public INode {
 public:
 	virtual ~IMainClass() = default;
};

class IClassDeclaration: public INode {
 public:
	virtual ~IClassDeclaration() = default;
};

class IVarDeclaration: public INode {
 public:
 	virtual ~IVarDeclaration() = default;
};

class IMethodDeclaration: public INode {
 public:
	virtual ~IMethodDeclaration() = default;
};

class IType: public INode {
 public:
	virtual ~IType() = default;
	
};

class IStatement: public INode {
 public:
 	virtual ~IStatement() = default;
};

class IExpression: public INode {
public:
	virtual ~IExpression() = default;

};

class IIdentifier: public INode {
public:
	virtual ~IIdentifier() = default;
	
};