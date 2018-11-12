#include "Type.h"
#include "../Visitor.h"


Type::Type(IIdentifier* name): name(name) {}
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
