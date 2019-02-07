#pragma once
#include "Symbol.h"
#include "MethodInfo.h"
#include "VariableInfo.h"
#include <unordered_map>

class ClassInfo{
 public:
 	ClassInfo(Symbol* name, Symbol* parent);

 	bool HasField(Symbol* name);
 	bool HasMethod(Symbol* name);
 	MethodInfo* GetMethod(Symbol* name);

 	Symbol* name;
 	Symbol* parent;
 	ClassInfo* parentInfo;
 	std::unordered_map<Symbol*, VariableInfo*> vars;
 	std::unordered_map<Symbol*, MethodInfo*> methods;
};
