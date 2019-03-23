// #include "../SymbolTable/Symbol.h"
#pragma once

#include "IRStatement.h"
#include "IRExpression.h"
#include <vector>
#include <string>

class MoveStatement : public IRStatement {
public:
    MoveStatement(IRExpression* dst, IRExpression* src);
    void Accept(IRVisitor* v) const override;

    IRExpression* dst;
    IRExpression* src;
};

class ExpStatement : public IRStatement {
public:
    ExpStatement(IRExpression* exp);
    void Accept(IRVisitor* v) const override;

    IRExpression* exp;
};

class JumpStatement : public IRStatement {
public:
    JumpStatement(std::string& label);
    void Accept(IRVisitor* v) const override;

    std::string label;
};

class CJumpStatement : public IRStatement {
public:
    enum Relation { LESS, NEQ, EQ };

    CJumpStatement(CJumpStatement::Relation rel, IRExpression* left, IRExpression* right,
                   std::string& if_left, std::string& if_right);
    void Accept(IRVisitor* v) const override;

    CJumpStatement::Relation rel;
    IRExpression* left;
    IRExpression* right;
    std::string if_left;
    std::string if_right;
};

class SeqStatement : public IRStatement {
public:
    SeqStatement(IRStatement* left, IRStatement* right);
    void Accept(IRVisitor* v) const override;

    IRStatement* left;
    IRStatement* right;
};

class LabelStatement : public IRStatement {
public:
    LabelStatement(std::string& label);
    void Accept(IRVisitor* v) const override;

    std::string label;
};
