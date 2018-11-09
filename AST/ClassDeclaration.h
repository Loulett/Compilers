#include "INode.h"
#include <vector>

class ClassDeclaration: public IClassDeclaration {
public:
	ClassDeclaration(IIdentifier* class_name, IIdentifier* extends_class_name, std::vector<IVarDeclaration*>* vars, std::vector<IMethodDeclaration*>* methods);
 private:
 	IIdentifier* class_name;
 	IIdentifier* extends_class_name;
 	std::vector<IVarDeclaration*>* vars;
 	std::vector<IMethodDeclaration*>* methods;
};