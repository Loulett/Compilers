// #include "../SymbolTable/Symbol.h"
#pragma once
// #ifndef IRTree_Expression
// #define IRTree_Expression

#include "IRExpression.h"
#include "IRStatement.h"
#include <vector>
#include <string>
#include <memory>

class IRExpList {
public:
    IRExpList() = default;
//    IRExpList( std::unique_ptr<const IRExpression> exp);
    void Add(IRExpression* exp);
//    std::vector< std::unique_ptr<const IRExpression> > Get();
    std::unique_ptr<const IRExpList> GetCopy() const;

    std::vector< std::unique_ptr<const IRExpression> > list;

    //std::unique_ptr<const IRExpression> GetCopy() const override;

    explicit IRExpList( const IRExpression* expression )
    {
        Add( expression );
    }

    void Add( const IRExpression* expression )
    {
        list.emplace_back( expression );
    }

    void Add( std::unique_ptr<const IRExpression> expression )
    {
        list.emplace_back( std::move( expression ) );
    }
//
//
//
//    std::unique_ptr<const IRExpList> GetCopy() const;

    bool is_commutative() {return false; }
    bool is_absolutely_commutative() {return false; }
};

class ConstExpression : public IRExpression {  //done
public:
    ConstExpression(int val);
    void Accept(IRVisitor* v) const override;

    std::unique_ptr<const IRExpression> GetCopy() const override;


    bool is_commutative() {return true; }
    bool is_absolutely_commutative() {return true; }

    int value;
};

class NameExpression : public IRExpression {    //done
public:
    NameExpression(std::string& name);
    void Accept(IRVisitor* v) const override;
    std::string name;

    std::unique_ptr<const IRExpression> GetCopy() const override;

    bool is_commutative() {return true; }
    bool is_absolutely_commutative() {return true; }
};

class TempExpression : public IRExpression {
public:
    TempExpression(std::string& name);
    void Accept(IRVisitor* v) const override;
    std::string name;

    std::unique_ptr<const IRExpression> GetCopy() const override;

    bool is_commutative() {return true; }
    bool is_absolutely_commutative() {return false; }   // 123 mb bug
};

class BinOpExpression : public IRExpression {
public:
    enum BinOp { PLUS, MINUS, MULT, DIV, REM, LESS, AND, OR };

    explicit BinOpExpression( BinOp binop, std::unique_ptr<const IRExpression> left, std::unique_ptr<const IRExpression> right ) :
            binop( binop ), left( std::move( left ) ), right( std::move( right ) )
    {
    }

    explicit BinOpExpression(BinOp binop, IRExpression* left, IRExpression* right);






    void Accept(IRVisitor* v) const override;

    std::unique_ptr<const IRExpression> GetCopy() const override;

    bool is_commutative() {return false; }
    bool is_absolutely_commutative() {return false; }


    BinOp binop;
    std::unique_ptr<const IRExpression> left;
    std::unique_ptr<const IRExpression> right;
};

class MemExpression : public IRExpression {
public:
    explicit MemExpression(IRExpression* expr);
    void Accept(IRVisitor* v) const override;
    std::unique_ptr<const IRExpression> expr;

    std::unique_ptr<const IRExpression> GetCopy() const override;
    //mb тут не нужен explicit
    explicit MemExpression( std::unique_ptr<const IRExpression> exp_ ) :
    expr( std::move( exp_ ) )
    {
    }


//    bool is_commutative() {return expr.is_absolutely_commutative(); }
//    bool is_absolutely_commutative() {return false; }
};

class CallExpression : public IRExpression {
public:
    CallExpression(IRExpression* func, IRExpList* args);
    void Accept(IRVisitor* v) const override;

    std::unique_ptr<const IRExpression> GetCopy() const override;

    CallExpression( std::unique_ptr<const IRExpression> funcExp, std::unique_ptr<const IRExpList> args ) :
            func( std::move( funcExp ) ), args( std::move( args ) )
    {
    }


    bool is_commutative() {return false; }
    bool is_absolutely_commutative() {return false; }

    std::unique_ptr<const IRExpression> func;
    std::unique_ptr<const IRExpList> args;
};

class ESeqExpression : public IRExpression {
public:
    ESeqExpression(IRStatement* stm, IRExpression* expr);
    void Accept(IRVisitor* v) const override;

    std::unique_ptr<const IRExpression> GetCopy() const override;

    ESeqExpression( std::unique_ptr<const IRStatement> stm, std::unique_ptr<const IRExpression> exp ) :
    stm( std::move( stm ) ), expr( std::move( exp ) )
    {
    }


    bool is_commutative() {return false; }
    bool is_absolutely_commutative() {return false; }

    std::unique_ptr<const IRStatement> stm;
    std::unique_ptr<const IRExpression> expr;

    // 123 mb bug
//    bool is_commutative() {return false; }
//    bool is_absolutely_commutative() {return false; }
};

// #endif  // IRTree_Expression
