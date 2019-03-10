#pragma once

#include "../Visitor.h"
#include "..ActivationRecords/IFrame.h"
#include "IStatement.h"
#include "../SymbolTable/TableBuilder.cpp"
#include "WrapperSubTree.h"

struct CCodeFragment {
    const IFrame* frame;
    const IRTree::IStatement* body;
};

class CTranslator : public IVisitor {
    IFrame* curFrame;
    std::vector<CCodeFragment> codeFragments;

    std::map<std::string, IFrame*> frames;

    ISubtreeWrapper* curWrapper;
    Table* symbolTable;
    ClassInfo* curClass;
    MethodInfo* curMethod;

    void buildNewFrame( const MethodDeclaration* declaration ) {
        ClassInfo* classDefinition = symbolTable->classes[curClass->name].get();
        MethodInfo* methodDefinition = classDefinition->methods[declaration->name->value].get();

        curFrame = new X86MiniJavaFrame( classDefinition->name, methodDefinition->name);

        for ( auto& it: ...) {  // by Frame
            // go through args of Frame classDef
        }
        for ( auto& it: ... ) {
            // go through args of Frame methodDef
        }

        frames.emplace( curFrame->GetName(),  curFrame );
    }


    void ProcessStatementList(const std::vector<std::unique_ptr<IStatement>>* statements) {

        WrapperSubtree* rightTail = nullptr;

        if (!statements->empty()) {
            statements->back()->Accept( this);
            rightTail = curWrapper;
        }
        for(auto&& stmt = std::next(statements->crbegin()); stmt != statements->crend(); ++stmt) {
            (*stmt)->Accept( this);
            auto curResult = curWrapper;
            rightTail = new WrapperStmt(new CSeqStatement(curResult->ToStm(), rightTail->ToStm()));
        }
        curWrapper = rightTail;
    }


    virtual void visit(const Goal* n)override;
    virtual void visit(const MainClass* n) override;
    virtual void visit(const ClassDeclaration* n) override;
    virtual void visit(const VarDeclaration* n) override;
    virtual void visit(const MethodDeclaration* n) override;

    virtual void visit(const Type* n) override;

    virtual void visit(const IfStatement* n) override;
    virtual void visit(const WhileStatement* n) override;
    virtual void visit(const Statement* n) override;
    virtual void visit(const PrintStatement* n) override;
    virtual void visit(const AssignmentStatement* n) override;
    virtual void visit(const ArrAssignmentStatement* n) override;

    virtual void visit(const MinusExpression* n) override;
    virtual void visit(const PlusExpression* n) override;
    virtual void visit(const AndExpression* n) override;
    virtual void visit(const LessExpression* n) override;
    virtual void visit(const MultExpression* n) override;


    virtual void visit(const RemainExpression* n) override;
    virtual void visit(const OrExpression* n) override;
    virtual void visit(const ArrayExpression* n) override;
    virtual void visit(const LengthExpression* n) override;
    virtual void visit(const MethodExpression* n) override;
    virtual void visit(const Integer* n) override;
    virtual void visit(const Bool* n) override;
    virtual void visit(const IdentExpression* n) override;
    virtual void visit(const This* n) override;
    virtual void visit(const NewArrExpression* n) override;
    virtual void visit(const NewExpression* n) override;
    virtual void visit(const NotExpression* n) override;
    virtual void visit(const Expression* n) override;

    virtual void visit(const Identifier* n) override;
};
