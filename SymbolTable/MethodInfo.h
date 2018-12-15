#include "Symbol.h"
#include "../AST/Type.h"
#include "VaribleInfo.h"
#include <unordered_map>

class MethodInfo {
 public:
 	MethodInfo(Type* type_, Symbol* name_)

 	Type* type;
 	Symbol* name;
 	std::unordered_map<Symbol*, VaribleInfo*> args;
 	std::unordered_map<Symbol*, VaribleInfo*> locals;
};