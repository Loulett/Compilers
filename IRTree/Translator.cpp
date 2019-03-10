#include "Translator.h"

Translator::Translator(Table* table): table(table) {}

void Translator::visit(const Goal* n) {
    n->main_class->Accept(this);
    for (auto cl: n->class_declarations) {
        cl->Accept(this);
    }
}

void Translator::visit(const MainClass* n) {
    auto name = dynamic_cast<Identifier*>(n->class_name.get())->name;
    curClass = table->classes[name];
    curMethod = curClass->methods[InternTable::getIntern("main")];
    BuildFrame(curClass, curMethod);

    n->statement->Accept(this);
    auto wrapper = std::move(curWrapper);
    curWrapper = new StmWrapper(
            new SeqStatement(
                new LabelStatement(curFrame->name),
                wrapper->ToStm()
            )
        );
    CodeFragment cf(curFrame, curWrapper->ToStm());
    fragments[curFrame->name] = std::move(cf);
    curClass = nullptr;
    curMethod = nullptr;
}


void Translator::visit(const ClassDeclaration* n) {
    auto name = dynamic_cast<Identifier*>(n->class_name.get())->name;
    curClass = table->classes[name];

    for (auto& met: *n->methods) {
        met->Accept(this);
    }

    curClass = nullptr;
}

void visit(const VarDeclaration*) { assert(false); }

void visit(const MethodDeclaration* n) {
    auto name = dynamic_cast<Identifier*>(n->name.get())->name;
    curMethod = curClass->methods[name];
    BuildFrame(curClass, curMethod);

    AcceptStms(n->statements);
    auto stm_wrapper = std::move(curWrapper);

    n->return_expression->Accept(this);
    auto return_exp = curWrapper->ToExp();

    if (stm_wrapper) {
        curWrapper = new StmWrapper(
                new SeqStatement(
                    new LabelStatement(curFrame->name),
                    new SeqStatement(
                        stm_wrapper->ToStm(),
                        MoveStatement(
                            ,
                            return_exp
                        )
                    )
                )
            )
    }

}


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
void Translator::visit(const Expression* n) {
    n->exp->Accept();
}

void Translator::visit(const Identifier*) {assert(false);}

void Translator::AddClassFields(ClassInfo* class_info) {
    if (class_info->parent != nullptr) {
        AddClassFields(class_info->parentInfo);
    }
    for (auto& var: class_info->vars) {
        curFrame->AddFormal(var.first->GetString());
    }
}

void Translator::AddMethodFields(MethodInfo* method_info) {
    for (auto& arg: method_info->arg) {
        curFrame->AddLocal(arg.first->GetString());
    }
    for (auto& loc: method_info->locals) {
        curFrame->AddLocal(loc.first->GetString());
    }
}

void Translator::BuildFrame(Symbol* class_name, Symbol* method_name) {
    ClassInfo* class_info = table->classes.find(class_name);
    MethodInfo* method_info = class_info->methods.find(method_name);

    curFrame = new X86MiniJavaFrame(class_name->GetString(), method_name->GetString());

    AddClassFields(class_info);
    AddMethodFields(method_info);
}
