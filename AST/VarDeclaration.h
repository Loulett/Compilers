#include "INode.h"

class VarDeclaration: public IVarDeclaration {
 public:
	VarDeclaration(IType* type, IIdentifier* name);

 private:
 	IType* type;
 	IIdentifier* name;
};