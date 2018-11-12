#pragma once
#include "INode.h"
#include <vector>

class Goal: public IGoal {
 public:
	Goal(IMainClass* main_class, std::vector<IClassDeclaration*>* class_declarations);
	void Accept(Visitor* v) const override;
 private:
 	IMainClass* main_class;
 	std::vector<IClassDeclaration*>* class_declarations;
};