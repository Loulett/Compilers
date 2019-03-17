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
                            curFrame->GetAccess(X86MiniJavaFrame::return_pointer)->ToExp(),
                            return_exp
                        )
                    )
                )
            );
    }
    CodeFragment cf(curFrame, curWrapper->ToStm());
    fragments[curFrame->name] = std::move(cf);
    curMethod = nullptr;
}


void Translator::visit(const Type*) {assert(false);}

void Translator::visit(const IfStatement* n) {
    n->clause->Accept(this);
    auto cond_wrapper = std::move(curWrapper);

    n->true_statement->Accept(this);
    auto true_wrapper = std::move(curWrapper);

    n->false_statement->Accept(this);
    auto false_wrapper = std::move(curWrapper);

    std::string true_label = "True::" + std::string(ifCounter);
    std::string false_label = "False::" + std::string(ifCounter);
    std::string exit_label = "IfExit::" + std::string(ifCounter);

    curWrapper = new StmWrapper(
            new SeqStatement(
                cond_wrapper->ToCond(true_label, false_label),
                new SeqStatement(
                    new LabelStatement(true_label),
                    new SeqStatement(
                        true_wrapper->ToStm(),
                        new SeqStatement(
                            new JumpStatement(exit_label),
                            new SeqStatement(
                                new LabelStatement(false_label),
                                new SeqStatement(
                                    false_wrapper->ToStm(),
                                    new LabelStatement(exit_label)
                                )
                            )
                        )
                    )
                )
            )
        );

    ifCounter++;
}

void Translator::visit(const WhileStatement* n) {
    n->clause->Accept(this);
    auto clause_wrapper = std::move(curWrapper);

    n->body->Accept(this);
    auto body_wrapper = std::move(curWrapper);

    std::string loop_label = "Loop::" + std::string(WhileCounter);
    std::string body_label = "Body::" + std::string(WhileCounter);
    std::string done_label = "Done::" + std::string(WhileCounter);

    curWrapper = new StmWrapper(
            new SeqStatement(
                new LabelStatement(loop_label),
                new SeqStatement(
                    clause_wrapper->ToCond(body_label, done_label),
                    new SeqStatement(
                        new LabelStatement(body_label),
                        new SeqStatement(
                            body_wrapper->ToStm(),
                            new SeqStatement(
                                new JumpStatement(loop_label),
                                new LabelStatement(done_label)
                            )
                        )
                    )
                )
            )
        );

    WhileCounter++;
}

void Traslator::visit(const Statement* n) {
    AcceptStms(n->statements);
}

void Translator::visit(const PrintStatement* n) {
    n->print->Accept(this);

    curWrapper = new ExpWrapper(
            curFrame->ExternalCall("print", curWrapper->ToExp())
        );
}

void Translator::visit(const AssignmentStatement* n) {
    n->var->Accept(this);
    auto var = curWrapper->ToExp();

    n->expr->Accept(this);
    auto expr = curWrapper->ToExp();

    curWrapper = new StmWrapper(
            new MoveStatement(
                expr,
                var
            )
        );
}

void Translator::visit(const ArrAssignmentStatement* n) {
    n->var->Accept(this);
    auto var = curWrapper->ToExp();

    n->num->Accept(this);
    auto num = curWrapper->ToExp();

    n->expr->Accept(this);
    auto expr = curWrapper->ToExp();

    curWrapper = new StmWrapper(
            new MoveStatement(
                expr,
                new MemExpression(
                    new BinOpExpression(
                        BinOpExpression::BinOp::PLUS,
                        var,
                        new BinOpExpression(
                            BinOpExpression::BinOp::MULT,
                            new BinOpExpression(
                                BinOpExpression::BinOp::PLUS,
                                num,
                                new ConstExpression(1)
                                ),
                            new ConstExpression(
                                curFrame->WordSize()
                            )
                        )
                    )
                )
            )
        );
}

void Translate::visit(const AndExpression* n) {
    n->expr1->Accept(this);
    auto expr1 = std::move(curWrapper);

    n->expr2->Accept(this);
    auto expr2 = std::move(curWrapper);

    curWrapper = new
}

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
