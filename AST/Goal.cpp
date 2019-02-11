#include "Goal.h"
#include "../Visitor.h"
#include <iostream>

Goal::Goal(IMainClass* main_class, std::vector<std::unique_ptr<IClassDeclaration>>* class_declarations) {
	if (main_class == nullptr || class_declarations == nullptr) {
		std::cout << "Nullptr encountered in Goal initializer";
	}
	this->main_class = std::unique_ptr<IMainClass>(main_class);
	this->class_declarations = std::unique_ptr<std::vector<std::unique_ptr<IClassDeclaration>>>(class_declarations);
}

void Goal::Accept(Visitor* v) const
{
	v->visit(this);
}
