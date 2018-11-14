#pragma once
#include "INode.h"
#include <vector>
#include <memory>

class ClassDeclaration: public IClassDeclaration {
public:
	ClassDeclaration(IIdentifier* class_name, IIdentifier* extends_class_name, std::vector<std::unique_ptr<IVarDeclaration>>* vars, std::vector<IMethodDeclaration*>* methods);
	void Accept(Visitor* v) const override;
 private:
 	IIdentifier* class_name;
 	IIdentifier* extends_class_name;
 	std::vector<std::unique_ptr<IVarDeclaration>>* vars;
 	std::vector<IMethodDeclaration*>* methods;
};