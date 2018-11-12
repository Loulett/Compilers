#pragma once
#include "INode.h"
#include "string"

class Identifier: public IIdentifier {
 public:
 	Identifier(std::string name);
    void Accept(Visitor* v) const;
 private:
 	std::string name;
};