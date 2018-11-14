#pragma once
#include "INode.h"
#include <memory>

class MainClass: public IMainClass {
 public:
	MainClass(IIdentifier* class_name, IIdentifier* arg, IStatement* statement);
    void Accept(Visitor* v) const override;
 private:
 	std::unique_ptr<IIdentifier> class_name;
	std::unique_ptr<IIdentifier> arg;
	std::unique_ptr<IStatement> statement;
};