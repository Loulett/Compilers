#pragma once
#include "INode.h"
#include <memory>
#include <variant>

struct IntType
{
};
struct BoolType
{
};
struct IntArrType
{
};
struct ClassType
{
    IIdentifier* name;
};


using TYPE = std::variant<IntType, BoolType, IntArrType, ClassType>;

struct Type: public IType
{
    TYPE type;
    template <typename T>
    Type(T&& t) : type(t) {}
    void Accept(Visitor* v) const;
};
