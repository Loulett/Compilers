#include "INode.h"
#include "string"

class Identifier: public IIdentifier {
 public:
 	Identifier(std::string name);
 private:
 	std::string name;
};