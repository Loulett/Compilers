#include "ClassDeclaration.h"
#include "../IVisitor.h"

ClassDeclaration::ClassDeclaration(IIdentifier* class_name, IIdentifier* extends_class_name, std::vector<IVarDeclaration*> vars, std::vector<IMethodDeclaration*> methods):
class_name(class_name), extends_class_name(extends_class_name), vars(vars), methods(methods) {}

void ClassDeclaration::Accept(IVisitor* v) const
{
    v->visit(this);
}
