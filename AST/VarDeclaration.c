#include "VarDeclaration.h"
#include "../IVisitor.h"

VarDeclaration::VarDeclaration(IType* type, IIdentifier* name):
	type(type), name(name) {}

void VarDeclaration::Accept(IVisitor* v) const
{
	v->visit(this);
}
