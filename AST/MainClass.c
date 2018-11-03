#include "MainClass.h"

MainClass::MainClass(IIdentifier* class_name, IIdentifier* arg, IStatement* statement):
	class_name(class_name), arg(arg), statement(statement) {}