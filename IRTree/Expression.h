// #include "../SymbolTable/Symbol.h"
#pragma once
// #ifndef IRTree_Expression
// #define IRTree_Expression

#include "IRExpression.h"
#include "IRStatement.h"
#include <vector>
#include <string>

class IRExpList {
 public:
    IRExpList() = default;
    IRExpList(IRExpression* exp);
    void Add(IRExpression* exp);
    std::vector<IRExpression*> Get();

    std::vector<IRExpression*> list;
};

class ConstExpression: public IRExpression {
 public:
    ConstExpression(int val);
    void Accept( IRVisitor* v ) const override;
    int value;
};

class NameExpression: public IRExpression {
 public:
    NameExpression(std::string& name);
    void Accept( IRVisitor* v ) const override;
    std::string name;
};

class TempExpression: public IRExpression {
 public:
    TempExpression(std::string& name);
    void Accept( IRVisitor* v ) const override;
    std::string name;
};

class BinOpExpression: public IRExpression {
 public:
    enum BinOp {
        PLUS,
        MINUS,
        MULT,
        DIV,
        REM,
        LESS,
        AND,
        OR
    };

    BinOpExpression(BinOp binop, IRExpression* left, IRExpression* right);
    void Accept( IRVisitor* v ) const override;

    BinOp binop;
    IRExpression* left;
    IRExpression* right;
};

class MemExpression: public IRExpression {
 public:
    MemExpression(IRExpression* expr);
    void Accept( IRVisitor* v ) const override;

    IRExpression* expr;

};

class CallExpression: public IRExpression {
 public:
    CallExpression(IRExpression* func, IRExpList* args);
    void Accept( IRVisitor* v ) const override;

    IRExpression* func;
    IRExpList* args;

};

class ESeqExpression: public IRExpression {
 public:
    ESeqExpression(IRStatement* stm, IRExpression* expr);
    void Accept( IRVisitor* v ) const override;

    IRStatement* stm;
    IRExpression* expr;

};

// #endif  // IRTree_Expression
