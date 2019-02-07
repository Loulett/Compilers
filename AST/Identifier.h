#pragma once
#include "INode.h"
#include "../SymbolTable/Symbol.h"
#include <string>

class Identifier: public IIdentifier {
 public:
 	Identifier(Symbol* name);
    void Accept(Visitor* v) const;
 public:
 	Symbol* name;
};
