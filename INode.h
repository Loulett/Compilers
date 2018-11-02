
class INode {	
};

class IGoal: public INode {
 public:
 	virtual ~IGoal() = default;
};

class IMainClass: public INode {
 public:
 	virtual ~IMainClass() = default;
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

class IIndetifier: public INode {
public:
	virtual ~IIndetifier() = default;
	
};