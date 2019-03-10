// #include "../SymbolTable/Symbol.h"
#include "Statement.h"
#include <vector>
#include <string>

class IRExpression {
};

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
    int value;
};

class NameExpression: public IRExpression {
 public:
    NameExpression(std::string& name);
    std::string name;
};

class TempExpression: public IRExpression {
 public:
    TempExpression(std::string& name);
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

    BinOp binop;
    IRExpression* left;
    IRExpression* right;
};

class MemExpression: public IRExpression {
 public:
    MemExpression(IRExpression* expr);

    IRExpression* expr;

};

class CallExpression: public IRExpression {
 public:
    CallExpression(IRExpression* func, IRExpList* args);

    IRExpression* func;
    IRExpList* args;

};

class ESeqExpression: public IRExpression {
 public:
    ESeqExpression(IRStatement* stm, IRExpression* expr);

    IRStatement* stm;
    IRExpression* expr;

};
