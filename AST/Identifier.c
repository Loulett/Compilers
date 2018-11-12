#include "Identifier.h"
#include "../Visitor.h"

Identifier::Identifier(std::string name): name(name) {}

void Identifier::Accept(Visitor* v) const
{
    v->visit(this);
}
