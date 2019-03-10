#include "../IRTree/Expression.h"

class IAccess {
    virtual ~IAccess() = default;
    virtual IRExpression* GetExp() = 0;
};
