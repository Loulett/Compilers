#pragma once

#include "utils.h"
#include "MethodInfo.h"

struct ClassInfo : public CBlock
{
    Symbol* name;
    Symbol* parent;
    std::map<Symbol*, CVarInfo*> fields;
    std::map<Symbol*, CMethodInfo*> methods;
    ClassInfo* parentInfo;
public:
    bool HasVarDeclared(Symbol* s) override {
        if ( fields.find( s ) != fields.end() ) {
            return true;
        }
        for ( auto& method: methods ) {
            if ( method.second->HasVarDeclared( s ) ) {}
            return true;
        }

        if ( parentInfo != nullptr ) {
            return parentInfo->HasVarDeclared( s );
        }

        return false;
    }

    CVarInfo* GetField(Symbol* s) {
        if ( fields.find( s ) != fields.end() ) {
            return fields[s];
        }

        if ( parentInfo != nullptr ) {
            return parentInfo->GetField( s );
        }

        return nullptr;
    }

    bool HasField(Symbol* s) {
        if ( fields.find( s ) != fields.end() ) {
            return true;
        }

        if ( parentInfo != nullptr ) {
            return parentInfo->HasField( s );
        }

        return false;
    }

    CMethodInfo* GetMethod(Symbol* s) {
        if ( methods.find( s ) != methods.end() ) {
            return methods[s];
        }

        if ( parentInfo != nullptr ) {
            return parentInfo->GetMethod( s );
        }

        return nullptr;
    }

    bool HasMethod(Symbol* s) {
        if ( methods.find( s ) != methods.end() ) {
            return true;
        }

        if ( parentInfo != nullptr ) {
            return parentInfo->HasMethod( s );
        }

        return false;
    }
};
