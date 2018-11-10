#include "INode.h"
#include <vector>
#include <utility>

class MethodDeclaration: public INode{
public:
	MethodDeclaration(IType* return_type, IIdentifier* name, std::vector<std::pair<IType*, IIdentifier*>> args, std::vector<IVarDeclaration*> vars, std::vector<IStatement*> statements, IExpression* return_expression);
    void Accept(IVisitor* v) const;
 private:
 	IType* return_type;
 	IIdentifier* name;
 	std::vector<std::pair<IType*, IIdentifier*>> args;
 	std::vector<IVarDeclaration*> vars;
 	std::vector<IStatement*> statements;
 	IExpression* return_expression;
};