#include "IAccess.h"
#include <src/IRTree/CIRExpression.h>


namespace IRTree
{

    class InRegAccess : public IAccess
    {
    public:
        explicit InRegAccess( const TempExpression& temp_ ) : temp( temp_ )
        {
        }

        IExpr* ToExpression() const override {
            return new TempExpression( temp );
        }

        TempExpression temp;
    };

}
