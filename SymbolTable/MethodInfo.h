#pragma once
#include "Symbol.h"
#include "../AST/Type.h"
#include "VariableInfo.h"
#include <unordered_map>

class MethodInfo {
 public:
 	MethodInfo(Type* type_, Symbol* name_);

 	Type* type;
 	Symbol* name;
 	std::unordered_map<Symbol*, VariableInfo*> args;
 	std::unordered_map<Symbol*, VariableInfo*> locals;
};
