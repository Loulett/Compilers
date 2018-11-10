#include "INode.h"
#include "string"

class Identifier: public IIdentifier {
 public:
 	Identifier(std::string name);
    void Accept(IVisitor* v) const;
 private:
 	std::string name;
};