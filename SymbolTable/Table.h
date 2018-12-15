#pragma once
#include "ClassInfo.h"
#include "Symbol.h"
#include <unordered_map>

class Table {
	std::unordered_map<Symbol*, ClassInfo*> classes;
};