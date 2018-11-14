#include "Identifier.h"
#include "../Visitor.h"
#include <iostream>

Identifier::Identifier(std::string name) {
	if (name.empty()) {
		std::cout << "Empty name in Identifier!\n";
	}
	this->name = name;
}

void Identifier::Accept(Visitor* v) const
{
    v->visit(this);
}
