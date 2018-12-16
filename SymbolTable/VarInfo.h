#pragma once

#include <Symbol.h>
#include <../AST/ITreeNodes.h>
#include "utils.h"

struct VarInfo {
    VarInfo() = default;
    VarInfo(Type* type_, Symbol* symbol_)  :
            type(type_), symbol(symbol_)
    {
    }
    Type* type;
    Symbol* symbol;
};
