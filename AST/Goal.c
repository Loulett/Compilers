#include "Goal.h"
#include "../IVisitor.h"

Goal::Goal(IMainClass* main_class, std::vector<IClassDeclaration*>* class_declarations):
	main_class(main_class), class_declarations(class_declarations) {}

void Goal::Accept(IVisitor* v) const
{
	v->visit(this);
}
