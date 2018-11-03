#include "VarDeclaration.h"

VarDeclaration::VarDeclaration(IType* type, IIdentifier* name):
	type(type), name(name) {}