#pragma once
#include "Symbol.h"
#include "../AST/Type.h"

class VariableInfo {
 public:
 	VariableInfo() = default;
 	VariableInfo(Type* type_, Symbol* symbol_);

 	Type* type;
 	Symbol* symbol;
};