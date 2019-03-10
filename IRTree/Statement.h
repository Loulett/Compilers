// #include "../SymbolTable/Symbol.h"
#include <vector>

class IRStatement {

};

class MoveStatement: public IRStatement {
 public:
    MoveStatement(IRExpression* dst, IRExpression* src);

    IRExpression* dst;
    IRExpression* src;
};

class ExpStatement: public IRStatement {
 public:
    ExpStatement(IRExpression* exp);

    IRExpression* exp;

};

class JumpStatement: public IRStatement {
 public:
    JumpStatement(IRExpression* exp);

    IRExpression* exp;
};

class CJumpStatement: public IRStatement {
 public:
    CJumpStatement(int rel, IRExpression* left, IRExpression* right, std::string& if_left, std::string& if_right);

    int rel;
    IRExpression* left;
    IRExpression* right;
    std::string& if_left;
    std::string& if_right;

};

class SeqStatement: public IRStatement {
 public:
    SeqStatement(IRStatement* left, IRStatement* right);

    IRStatement* left;
    IRStatement* right;
};

class LabelStatement: public IRStatement {
 public:
    LabelStatement(Symbol* label);

    Symbol* label;

};
