#include "Identifier.h"
#include "../IVisitor.h"

Identifier::Identifier(std::string name): name(name) {}

void Identifier::Accept(IVisitor* v) const
{
    v->visit(this);
}
