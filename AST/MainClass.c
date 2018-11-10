#include "MainClass.h"
#include "../Visitor.c"

MainClass::MainClass(IIdentifier* class_name, IIdentifier* arg, IStatement* statement):
	class_name(class_name), arg(arg), statement(statement) {}

void MainClass::Accept(IVisitor* v) const
{
	v->visit(this);
}
