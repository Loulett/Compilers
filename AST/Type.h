#pragma once
#include "INode.h"
#include <memory>

class IntType: public IType {
 public:
    void Accept(Visitor* v) const;
};

class BoolType: public IType {
 public:
    void Accept(Visitor* v) const;
};

class IntArrayType: public IType {
 public:
    void Accept(Visitor* v) const;
};

class Type: public IType {
 public:
 	Type(IIdentifier* name);
    void Accept(Visitor* v) const;
 private:
 	std::unique_ptr<IIdentifier> name;
};