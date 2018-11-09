#include "ClassDeclaration.h"

ClassDeclaration::ClassDeclaration(IIdentifier* class_name, IIdentifier* extends_class_name, std::vector<IVarDeclaration*>* vars, std::vector<IMethodDeclaration*>* methods):
class_name(class_name), extends_class_name(extends_class_name), vars(vars), methods(methods) {}