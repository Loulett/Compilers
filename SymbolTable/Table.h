#pragma once

#include <map>
#include <vector>
#include "ClassInfo.h"
#include "CBlock.h"

struct Table : public CBlock {
    std::vector<CBlock*> blocks;
    bool HasVarDeclared(Symbol* s) override;

    std::map<Symbol*, CClassInfo*> classes;
};
