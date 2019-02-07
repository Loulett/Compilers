#pragma once
#include "INode.h"
#include <memory>

class VarDeclaration: public IVarDeclaration {
 public:
	VarDeclaration(IType* type, IIdentifier* name);
    void Accept(Visitor* v) const;
 public:
 	std::unique_ptr<IType> type;
 	std::unique_ptr<IIdentifier> name;
};
