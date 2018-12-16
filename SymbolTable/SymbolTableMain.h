#pragma once

#include <src/common.h>
#include <cassert>
#include "../Visitor.h"
#include "Table.h"
#include "MethodInfo.h"
#include "utils.h"

class SymbolTableMain : public Visitor
{
private:
    std::unique_ptr<Table> table;
    std::unique_ptr<ClassInfo> curClass;
    std::unique_ptr<MethodInfo> curMethod;
    std::unique_ptr<VarInfo> curVariable;
    std::vector<std::string> errors;

    // Возвращает true,если className есть в таблице
    bool hasClass(Symbol* className);

public:
    Table* buildTable(Goal* ast) {
        visit(ast);
        return table;
    }

    void printErrors() {
        for (int i = 0; i< errors.size(); ++i) {
            printf("ERROR %d: %s", i, errors[i].c_str());
        }
        if (!errors.empty()) {
            throw CompilerException();
        }
    }

    explicit SymbolTableMain( );

    void visit(const Goal* n) override;
    void visit(const MainClass* n) override;
    void visit(const ClassDeclaration* n) override;
    void visit(const VarDeclaration* n) override;
    void visit(const MethodDeclaration* n) override;

    void visit(const IntType* n) override;
    void visit(const BoolType* n) override;
    void visit(const IntArrayType* n) override;
    void visit(const Type* n) override;

    void visit(const IfStatement* n) override;
    void visit(const WhileStatement* n) override;
    void visit(const Statement* n) override;
    void visit(const PrintStatement* n) override;
    void visit(const AssignmentStatement* n) override;
    void visit(const ArrAssignmentStatement* n) override;

    void visit(const AndExpression* n) override;

    void visit(const LessExpression* n) override;

    void visit(const PlusExpression* n) override;

    void visit(const MinusExpression* n) override;

    void visit(const MultExpression* n) override;

    void visit(const OrExpression* n) override;

    void visit(const RemainExpression* n) override;




    void visit(const ArrayExpression* n) override;

    void visit(const LengthExpression* n) override;

    void visit(const MethodExpression* n) override;

    void visit(const Integer* n) override;

    void visit(const Bool* n) override;

    void visit(const IdentExpression* n) override;

    void visit(const This* n) override;

    void visit(const NewArrExpression* n) override;

    void visit(const NewExpression* n) override;

    void visit(const NotExpression* n) override;

    void visit(const Expression* n) override;

    void visit(const Identifier* n) override;
};
