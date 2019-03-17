#include "SubTreeWrapper.h"

ExpWrapper::ExpWrapper(IRExpression* exp): exp(exp) {}

IRExpression* ExpWrapper::ToExp() {
    return exp;
}

IRStatement* ExpWrapper::ToStm() {
    return new ExpStatement(exp);
}

StmWrapper::StmWrapper(IRStatement* stm): stm(stm) {}

IRStatement* StmWrapper::ToStm() {
    return stm;
}
