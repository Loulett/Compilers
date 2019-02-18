#pragma once

#include "IExpression.h"
#include "IStatement.h"

namespace IRTree {

    template <class T>
    class List {
        // arguments
    };

    using ExpList = List<IExpression>;
    using StmList = List<IStatement>;

}