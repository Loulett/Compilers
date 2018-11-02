#include "INode.h"

class MainClass: public IMainClass {
 public:
	MainClass(IIdentifier* class_name, IIdentifier* arg, IStatement* statement);
 private:
 	IIdentifier* class_name;
	IIdentifier* arg;
	IStatement* statement;
};