#pragma once

#include <vector>
#include <memory>
#include "IExpression.h"
#include "IStatement.h"

namespace IRTree {

    class ExpressionsList {
    public:
        ExpressionsList() = default;

        explicit ExpressionsList( const IExpr* expression ) { Add( expression ); }

        void Add( const IExpr* expression ) { expressions.emplace_back( expression ); }


    private:
        std::vector<std::unique_ptr<const IExpr>> expressions;
    };
}
