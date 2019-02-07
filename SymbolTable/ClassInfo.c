#include "ClassInfo.h"

ClassInfo::ClassInfo(Symbol* name, Symbol* parent): name(name), parent(parent), parentInfo(nullptr) {}

bool ClassInfo::HasField (Symbol* name) {
	if (vars.find(name) != vars.end()) {
		return true;
	}
	if (parentInfo != nullptr) {
		return parentInfo->HasField(name);
	}
	return false;
}

bool ClassInfo::HasMethod (Symbol* name) {
	if (methods.find(name) != methods.end()) {
		return true;
	}
	if (parentInfo != nullptr) {
		return parentInfo->HasMethod(name);
	}
	return false;
}

MethodInfo* ClassInfo::GetMethod (Symbol* name) {
	if (methods.find(name) != methods.end()) {
		return methods[name];
	}
	if (parentInfo != nullptr) {
		return parentInfo->GetMethod(name);
	}
	return nullptr;
}
