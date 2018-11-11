#include "Type.h"


Type::Type(IIdentifier* name): name(name) {}
void Type::Accept(IVisitor* v) const
{
    v->visit(this);
}

IntType::Type(IIdentifier* name): name(name) {}
void IntType::Accept(IVisitor* v) const
{
    v->visit(this);
}

BoolType::Type(IIdentifier* name): name(name) {}
void BoolType::Accept(IVisitor* v) const
{
    v->visit(this);
}

IntArrayType::Type(IIdentifier* name): name(name) {}
void IntArrayType::Accept(IVisitor* v) const
{
    v->visit(this);
}
