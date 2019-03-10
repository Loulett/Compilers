#include "IAccess.h"
#include <../AST/Expression.h>
#include <../IRTree/IExpression.h>

namespace IRTree
{
    using namespace IRTree;

    class InFrameAccess : public IAccess
    {
    public:
        InFrameAccess( const IAccess* access_, const int offset_ ) : frameAccess( access_ ), offset( offset_ )
        {
        }

        IExpr* ToExpression() const override {
            const IExpr* offsetExpression;
            if ( offset != 0 ) {
                offsetExpression =
                        new BINOP(
                                BINOP::BINOP::PLUS,
                                frameAccess->ToExpression(),
                                new ConstExpression( offset )
                        );
            } else {
                offsetExpression = frameAccess->ToExpression();
            }
            return new MemoryExpression( offsetExpression );
        }

        const IAccess* frameAddress;
        int offset;
    };
}

