#include "VarDeclaration.h"
#include "../Visitor.h"
#include <iostream>

VarDeclaration::VarDeclaration(IType* type, IIdentifier* name) {
	if (type == nullptr || name == nullptr) {
		std::cout << "Nullptr encountered in VarDeclaration initializer.\n";
	}
	this->type = std::unique_ptr<IType>(type);
	this->name = std::unique_ptr<IIdentifier>(name);
}

void VarDeclaration::Accept(Visitor* v) const
{
	v->visit(this);
}
