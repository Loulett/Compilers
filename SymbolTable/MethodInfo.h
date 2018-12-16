#pragma once

#include "utils.h"
#include "CBlock.h"
#include "VarInfo.h"


struct MethodInfo : public CBlock
{
    Symbol* name;
    Type* retType;
    std::map<Symbol*, CVarInfo*> args;
    std::map<Symbol*, CVarInfo*> locals;

    MethodInfo() = default;
    MethodInfo( Symbol* name_, Type* retType_) : name(name_), retType(retType_)
    {}
    bool HasVarDeclared( Symbol* s ) override
    {
        if ( args.find( s ) != args.end()) {
            return true;
        }
        if ( locals.find( s ) != locals.end()) {
            return true;
        }
        return false;
    }
};
