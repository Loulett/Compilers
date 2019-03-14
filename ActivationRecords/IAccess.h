#include "../IRTree/IExpression.h"

namespace IRTree
{
    class IAccess
    {
    public:
        virtual ~IAccess() = default;
        virtual IExpr* ToExpression() const = 0;
    };
}