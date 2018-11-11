#include "INode.h"

class MainClass: public IMainClass {
 public:
	MainClass(IIdentifier* class_name, IIdentifier* arg, IStatement* statement);
    void Accept(IVisitor* v) const override;
 private:
 	IIdentifier* class_name;
	IIdentifier* arg;
	IStatement* statement;
};