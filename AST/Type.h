#include "INode.h"

class IntType: public IType {
};

class BoolType: public IType {
};

class IntArrayType: public IType {
};

class Type: public IType {
 public:
 	Type(IIdentifier* name);
 private:
 	IIdentifier* name;
};