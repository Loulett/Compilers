#include "MethodDeclaration.h"
#include "../Visitor.h"


MethodDeclaration::MethodDeclaration(IType* return_type, IIdentifier* name, std::vector<std::pair<IType*, IIdentifier*>>* args, std::vector<IVarDeclaration*>* vars, std::vector<IStatement*>* statements, IExpression* return_expression):
	return_type(return_type), name(name), args(args), vars(vars), statements(statements), return_expression(return_expression) {}

void MethodDeclaration::Accept(Visitor* v) const
{
    v->visit(this);
}
