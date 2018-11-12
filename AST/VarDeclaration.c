#include "VarDeclaration.h"
#include "../Visitor.h"

VarDeclaration::VarDeclaration(IType* type, IIdentifier* name):
	type(type), name(name) {}

void VarDeclaration::Accept(Visitor* v) const
{
	v->visit(this);
}
