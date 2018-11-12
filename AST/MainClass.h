#pragma once
#include "INode.h"

class MainClass: public IMainClass {
 public:
	MainClass(IIdentifier* class_name, IIdentifier* arg, IStatement* statement);
    void Accept(Visitor* v) const override;
 private:
 	IIdentifier* class_name;
	IIdentifier* arg;
	IStatement* statement;
};