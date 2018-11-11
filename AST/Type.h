#pragma once
#include "INode.h"

class IntType: public IType {
 public:
    void Accept(IVisitor* v) const;
};

class BoolType: public IType {
 public:
    void Accept(IVisitor* v) const;
};

class IntArrayType: public IType {
 public:
    void Accept(IVisitor* v) const;
};

class Type: public IType {
 public:
 	Type(IIdentifier* name);
    void Accept(IVisitor* v) const;
 private:
 	IIdentifier* name;
};