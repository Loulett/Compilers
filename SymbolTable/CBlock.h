#pragma once

#include "Symbol.h"

struct CBlock {
    virtual bool HasVarDeclared(Symbol* s) = 0;
};
