#include "MainClass.h"
#include "../Visitor.h"
#include <iostream>

MainClass::MainClass(IIdentifier* class_name, IIdentifier* arg, IStatement* statement) {
	if (class_name == nullptr || arg == nullptr || statement == nullptr) {
		std::cout << "Nullptr encountered in MainClass initializer.\n";
	}
	this->class_name = std::unique_ptr<IIdentifier>(class_name);
	this->arg = std::unique_ptr<IIdentifier>(arg);
	this->statement = std::unique_ptr<IStatement>(statement);
}

void MainClass::Accept(Visitor* v) const
{
	v->visit(this);
}
