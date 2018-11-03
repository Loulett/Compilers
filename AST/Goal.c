#include "Goal.h"

Goal::Goal(IMainClass* main_class, std::vector<IClassDeclaration*> class_declarations):
	main_class(main_class), class_declarations(class_declarations) {}