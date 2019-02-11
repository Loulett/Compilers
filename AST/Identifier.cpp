#include "Identifier.h"
#include "../Visitor.h"
#include <iostream>

Identifier::Identifier(Symbol* name) {
	if (name == nullptr) {
		std::cout << "Empty name in Identifier!\n";
	}
	this->name = name;
}

void Identifier::Accept(Visitor* v) const
{
    v->visit(this);
}
