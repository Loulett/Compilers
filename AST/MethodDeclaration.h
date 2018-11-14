#pragma once
#include "INode.h"
#include <vector>
#include <utility>
#include <memory>

class MethodDeclaration: public IMethodDeclaration{
public:
	MethodDeclaration(IType* return_type, IIdentifier* name, std::vector<std::pair<IType*, IIdentifier*>>* args, std::vector<IVarDeclaration*>* vars, std::vector<std::unique_ptr<IStatement>>* statements, IExpression* return_expression);
  void Accept(Visitor* v) const;
 private:
 	IType* return_type;
 	IIdentifier* name;
 	std::vector<std::pair<IType*, IIdentifier*>>* args;
 	std::vector<IVarDeclaration*>* vars;
 	std::vector<std::unique_ptr<IStatement>>* statements;
 	IExpression* return_expression;
};