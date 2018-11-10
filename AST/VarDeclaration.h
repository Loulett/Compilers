#include "INode.h"

class VarDeclaration: public IVarDeclaration {
 public:
	VarDeclaration(IType* type, IIdentifier* name);
    void Accept(IVisitor* v) const;
 private:
 	IType* type;
 	IIdentifier* name;
};