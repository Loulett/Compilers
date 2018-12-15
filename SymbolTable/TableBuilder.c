#include "TableBuilder.h"

TableBuilder::TableBuilder(): table(new Table), cl(nullptr), method(nullptr), var(nullptr) {}

void TableBuilder::visit(const Goal* n) {
	n->main_class->Accept(this);
	for (auto& class: *(n->class_declarations)) {
		class->Accept(this);
	}
}

void TableBuilder::visit(const MainClass* n) {
	cl = new ClassInfo(n->class_name->name, nullptr);
	method = new MethodInfo(getIndent("main"), nullptr);
	var = new VariableInfo(nullptr, n->arg->name)
	method->args[n->arg->name] = var;
	cl->methods[method->name] = method;
	table->classes[cl->name] = cl;
	var = 0;
	method = 0;
	cl = 0;
}

void TableBuilder::visit(const ClassDeclaration* n) {
	cl = new ClassInfo(n->class_name->name, n->extends_class_name == nullptr ? nullptr : n->extends_class_name->name);
	table->classes[cl->name] = cl;
	for ( auto& varDeclaration: *(n->varDeclarations)) {
        varDeclaration->Accept(this);
    }
    for ( auto& methodDeclaration: *(n->methodDeclarations)) {
        methodDeclaration->Accept(this);
    }
    cl = 0;
}

void TableBuilder::visit(const VarDeclaration* n) {
	var = new VariableInfo(n->type, n->name->name);
	if (method != nullptr) {
		method->locals[n->name->name] = var;
	} else {
		class->vars[n->name->name] = var;
	}
	var = 0;

}

void TableBuilder::visit(const MethodDeclaration* n) {
	method = new MethodInfo(n->return_type, n->name->name);
	cl->methods[method->name] = method;
}










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
    void visit(const Expression* n) {}

    void visit(const Identifier* n) {}