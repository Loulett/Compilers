#pragma once

#include "IExpression.h"
#include "IStatement.h"

namespace IRTree {

    template <class T>
    class List {
        // arguments
    };

    using ExpList = List<IExpr>;
    using StmList = List<IStatement>;

}