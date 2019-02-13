#include "Type.h"
#include "../Visitor.h"
#include <iostream>


Type::Type(IIdentifier* name) {
	if (name == nullptr) {
		std::cout << "Type name is empty.\n";
	}
	this->name = std::unique_ptr<IIdentifier>(name);
}

void Type::Accept(Visitor* v) const
{
    v->visit(this);
}


void IntType::Accept(Visitor* v) const
{
    v->visit(this);
}

void BoolType::Accept(Visitor* v) const
{
    v->visit(this);
}

void IntArrayType::Accept(Visitor* v) const
{
    v->visit(this);
}
