#include "TableBuilder.h"
#include "Symbol.h"
#include <cassert>
#include <iostream>

TableBuilder::TableBuilder(): table(new Table), curClass(nullptr), curMethod(nullptr), curVar(nullptr), curType(TYPE(NoneType{})), valExpr(true) {}

bool TableBuilder::hasClass(Symbol* className)
{
    return table->classes.find(className) != table->classes.end();
}

void TableBuilder::visit(const Goal* n) {
	for (auto& classDecl: *(n->class_declarations)) {
		classDecl->Accept(this);
	}
    n->main_class->Accept(this);

    for (auto& classDecl: *n->class_declarations) {
        curClass = table->classes[dynamic_cast<Identifier*>(dynamic_cast<ClassDeclaration*>(classDecl.get())->class_name.get())->name];
        for (auto& cl: table->classes) {
            if (cl.second->parent != nullptr && cl.second->parent == curClass->name) {
                cl.second->parentInfo = curClass;
                for (auto& var: cl.second->vars) {
                    if (curClass->HasField(var.second->symbol)) {
                        std::cout << "error: variable already was declared\n";
                        errors.push_back("error: variable already was declared\n");
                    }
                }

                for (auto& met: cl.second->methods) {
                    if (curClass->HasMethod(met.second->name)) {
                        auto method = curClass->GetMethod(met.second->name);
                        if (method->type->type != met.second->type->type ||
                            method->args.size() != met.second->args.size()) {
                            std::cout << "error: method already was declared -- 1\n";
                            errors.push_back("error: method already was declared -- 1\n");
                        } else {
                            for (auto arg1 = method->args.begin(), arg2 = met.second->args.begin();
                                arg1 != method->args.end();
                                arg1++, arg2++) {
                                if (arg1->second->type->type != arg2->second->type->type) {
                                    std::cout << "error: method already was declared -- 2\n";
                                    errors.push_back("error: method already was declared -- 2\n");
                                    break;
                                }
                            }
                        }
                    }
                    for (auto& arg: met.second->args) {
                        if (auto classVal = std::get_if<ClassType>(&(arg.second->type->type))) {
                            if (table->classes.find(classVal->name) == table->classes.end()) {
                                std::cout << "error: type of arg was not declared yet\n";
                                errors.push_back("error: type of arg was not declared yet\n");
                            }
                        }
                    }
                    if (auto classVal = std::get_if<ClassType>(&(met.second->type->type))) {
                        if (table->classes.find(classVal->name) == table->classes.end()) {
                            std::cout << "error: type of method was not declared yet\n";
                            errors.push_back("error: type of method was not declared yet\n");
                        }
                    }
                }
            }
        }
        curClass = nullptr;
    }

    for (auto& classDecl: *n->class_declarations) {
        curClass = table->classes[dynamic_cast<Identifier*>(dynamic_cast<ClassDeclaration*>(classDecl.get())->class_name.get())->name];
        if (curClass->parent != nullptr && (curClass->parentInfo == nullptr || curClass->parentInfo->parent == curClass->name)) {
            std::cout << "error: class extension\n";
            errors.push_back("error: class extension\n");
        }

        for (auto& met: curClass->methods) {
            for (auto& arg: met.second->args) {
                if (auto classVal = std::get_if<ClassType>(&(arg.second->type->type))) {
                    if (table->classes.find(classVal->name) == table->classes.end()) {
                        std::cout << "error: type of arg was not declared yet\n";
                        errors.push_back("error: type of arg was not declared yet\n");
                    }
                }
            }
            if (auto classVal = std::get_if<ClassType>(&(met.second->type->type))) {
                if (table->classes.find(classVal->name) == table->classes.end()) {
                    std::cout << "error: type of method was not declared yet\n";
                    errors.push_back("error: type of method was not declared yet\n");
                }
            }
        }
        curClass = nullptr;
    }
}

void TableBuilder::visit(const MainClass* n) {
	curClass = new ClassInfo(dynamic_cast<Identifier*>(n->class_name.get())->name, nullptr);

    if (hasClass(curClass->name)) {
        std::cout << "error: class already was declared.\n";
        errors.push_back("error: class already was declared.\n");
    }

    table->classes[curClass->name] = curClass;

    curMethod = new MethodInfo(nullptr, InternTable::getIntern("main"));
    curVar = new VariableInfo(nullptr, dynamic_cast<Identifier*>(n->arg.get())->name);
    curMethod->args[curVar->symbol] = curVar;
    curClass->methods[curMethod->name] = curMethod;
    n->statement->Accept(this);

	curClass = nullptr;
    curMethod = nullptr;
    curVar = nullptr;
}

void TableBuilder::visit(const ClassDeclaration* n) {
	curClass = new ClassInfo(dynamic_cast<Identifier*>(n->class_name.get())->name,
        n->extends_class_name == nullptr ? nullptr : dynamic_cast<Identifier*>(n->extends_class_name.get())->name);

    if (hasClass(curClass->name)) {
        std::cout << "error: class already was declared -- 2\n";
        errors.push_back("error: class already was declared.\n");
    }
	table->classes[curClass->name] = curClass;
	for (auto& varDeclaration: *(n->vars)) {
        varDeclaration->Accept(this);
    }
    for (auto methodDeclaration = n->methods->rbegin(); methodDeclaration != n->methods->rend(); methodDeclaration++) {
        methodDeclaration->get()->Accept(this);
    }
    curClass = nullptr;
}

void TableBuilder::visit(const VarDeclaration* n) {
	curVar = new VariableInfo(dynamic_cast<Type*>(n->type.get()), dynamic_cast<Identifier*>(n->name.get())->name);
	if (curMethod != nullptr) {
        if (curMethod->locals.find(curVar->symbol) != curMethod->locals.end()) {
            std::cout << "error: var already was declared as local var.\n";
            errors.push_back("error: var already was declared as local var.\n");
        }
        curMethod->locals[curVar->symbol] = curVar;
	} else {
		if (curClass->HasField(curVar->symbol)) {
            std::cout << "error: var already was declared as class field.\n";
            errors.push_back("error: var already was declared as class field.\n");
        }
        curClass->vars[curVar->symbol] = curVar;
	}
	curVar = nullptr;
}

void TableBuilder::visit(const MethodDeclaration* n) {
	curMethod = new MethodInfo(dynamic_cast<Type*>(n->return_type.get()), dynamic_cast<Identifier*>(n->name.get())->name);

    for (auto& var: *n->vars) {
        var->Accept(this);
    }

    for (auto& arg: *n->args) {
        curVar = new VariableInfo(dynamic_cast<Type*>(arg.first.get()), dynamic_cast<Identifier*>(arg.second.get())->name);
        if (curMethod->args.find(curVar->symbol) != curMethod->args.end()) {
            std::cout << "error: Arg was already declared.\n";
            errors.push_back("error: Arg was already declared.\n");
        }
        curMethod->args[curVar->symbol] = curVar;
    }

    if (curClass->HasMethod(curMethod->name)) {
        auto method = curClass->GetMethod(curMethod->name);
        if (method->args.size() != curMethod->args.size()) {
            std::cout << "error: Method was already declared.\n";
            errors.push_back("error: Method was already declared.\n");
        }
        else {
            for (auto arg1 = method->args.begin(), arg2 = curMethod->args.begin();
                arg1 != method->args.end();
                arg1++, arg2++) {
                if (arg1->second->type->type != arg2->second->type->type) {
                    std::cout << "error: method already was declared -- 2\n";
                    errors.push_back("error: method already was declared -- 2\n");
                    break;
                }
            }
        }
    }

    curClass->methods[curMethod->name] = curMethod;

    for (auto& stat: *n->statements) {
        stat->Accept(this);
    }

    n->return_expression->Accept(this);
    if (valExpr && curType != *(curMethod->type)) {
        std::cout << "error: Wrong type returned\n";
        errors.push_back("error: Wrong type returned\n");
    }
    valExpr = true;
    curType = Type(NoneType{});
    curMethod = nullptr;
}


void TableBuilder::visit(const Type*) {assert(false);}

void TableBuilder::visit(const IfStatement* n) {
    n->clause->Accept(this);
    if (valExpr && curType != Type(BoolType{})) {
        std::cout << "error: if clause should have bool type.\n";
        errors.push_back("error: if clause should have bool type.\n");
    }
    valExpr = true;
    curType = Type(NoneType{});
    n->true_statement->Accept(this);
    n->false_statement->Accept(this);

}
void TableBuilder::visit(const WhileStatement* n) {
    n->clause->Accept(this);
    if (valExpr && curType != Type(BoolType{})) {
        std::cout << "error: while clause should have bool type.\n";
        errors.push_back("error: while clause should have bool type.\n");
    }
    valExpr = true;
    curType = Type(NoneType{});
    n->body->Accept(this);
}

void TableBuilder::visit(const Statement* n) {
    for (auto& stat: *(n->statements)) {
        stat->Accept(this);
    }
}

void TableBuilder::visit(const PrintStatement* n) {
    n->print->Accept(this);
    if (valExpr && curType != Type(IntType{})) {
        std::cout << "error: wrong type for printing\n";
        errors.push_back("error: wrong type for printing\n");
    }
}

void TableBuilder::visit(const AssignmentStatement* n) {
    n->expr->Accept(this);
    if (curMethod->locals.find(dynamic_cast<Identifier*>(n->var.get())->name) != curMethod->locals.end()) {
        auto var = curMethod->locals.find(dynamic_cast<Identifier*>(n->var.get())->name)->second;
        if (valExpr && curType != *(var->type)) {
            std::cout << "error: type mismatch while assigning.\n";
            errors.push_back("error: type mismatch while assigning.\n");
        }
    }
    else if (curClass->vars.find(dynamic_cast<Identifier*>(n->var.get())->name) != curClass->vars.end()) {
        auto var = curClass->vars.find(dynamic_cast<Identifier*>(n->var.get())->name)->second;
        if (valExpr && curType != *(var->type)) {
            std::cout << "error: type mismatch while assigning.\n";
            errors.push_back("error: type mismatch while assigning.\n");
        }
    }
    else {
        std::cout << "error: variable " << dynamic_cast<Identifier*>(n->var.get())->name->getString() << " doesn't exist\n";
        errors.push_back("error: variable doesn't exist\n");
    }
    valExpr = true;
    curType = Type(NoneType{});
}

void TableBuilder::visit(const ArrAssignmentStatement* n) {
    n->num->Accept(this);
    if (valExpr && curType != Type(IntType{})) {
        std::cout << "error: array index can only be an integer.\n";
        errors.push_back("error: array index can only be an integer.\n");
    }
    valExpr = true;
    curType = Type(NoneType{});

    n->expr->Accept(this);
    if (valExpr && curType != Type(IntType{})) {
        std::cout << "error: type mismatch while assigning.\n";
        errors.push_back("error: type mismatch while assigning.\n");
    }
    valExpr = true;
    curType = Type(NoneType{});
    if (curMethod->locals.find(dynamic_cast<Identifier*>(n->var.get())->name) == curMethod->locals.end() &&
        curClass->vars.find(dynamic_cast<Identifier*>(n->var.get())->name) == curClass->vars.end()) {
        std::cout << "error: variable " << dynamic_cast<Identifier*>(n->var.get())->name->getString() << " doesn't exist 22\n";
        errors.push_back("error: variable doesn't exist\n");
    }
}

void TableBuilder::visit(const AndExpression* n) {
    n->expr1->Accept(this);
    if (curType != Type(BoolType{})) {
        valExpr = false;
        std::cout << "error: type mismatch.\n";
        errors.push_back("error: type mismatch.\n");
    }
    curType = Type(NoneType{});
    n->expr2->Accept(this);
    if (curType != Type(BoolType{})) {
        valExpr = false;
        std::cout << "error: type mismatch.\n";
        errors.push_back("error: type mismatch.\n");
    }
    curType = Type(BoolType{});
}
void TableBuilder::visit(const LessExpression* n) {
    n->expr1->Accept(this);
    if (curType != Type(IntType{})) {
        valExpr = false;
        std::cout << "error: type mismatch in less 1.\n";
        errors.push_back("error: type mismatch.\n");
    }
    curType = Type(NoneType{});
    n->expr2->Accept(this);
    if (curType != Type(IntType{})) {
        valExpr = false;
        std::cout << "error: type mismatch in less 2.\n";
        errors.push_back("error: type mismatch.\n");
    }
    curType = Type(BoolType{});
}
void TableBuilder::visit(const PlusExpression* n) {
    n->expr1->Accept(this);
    if (curType != Type(IntType{})) {
        valExpr = false;
        std::cout << "error: type mismatch.\n";
        errors.push_back("error: type mismatch.\n");
    }
    curType = Type(NoneType{});
    n->expr2->Accept(this);
    if (curType != Type(IntType{})) {
        valExpr = false;
        std::cout << "error: type mismatch.\n";
        errors.push_back("error: type mismatch.\n");
    }
    curType = Type(IntType{});
}

void TableBuilder::visit(const MinusExpression* n) {
    n->expr1->Accept(this);
    if (curType != Type(IntType{})) {
        valExpr = false;
        std::cout << "error: type mismatch.\n";
        errors.push_back("error: type mismatch.\n");
    }
    curType = Type(NoneType{});
    n->expr2->Accept(this);
    if (curType != Type(IntType{})) {
        valExpr = false;
        std::cout << "error: type mismatch.\n";
        errors.push_back("error: type mismatch.\n");
    }
    curType = Type(IntType{});
}

void TableBuilder::visit(const MultExpression* n) {
    n->expr1->Accept(this);
    if (curType != Type(IntType{})) {
        valExpr = false;
        std::cout << "error: type mismatch.\n";
        errors.push_back("error: type mismatch.\n");
    }
    curType = Type(NoneType{});
    n->expr2->Accept(this);
    if (curType != Type(IntType{})) {
        valExpr = false;
        std::cout << "error: type mismatch.\n";
        errors.push_back("error: type mismatch.\n");
    }
    curType = Type(IntType{});
}

void TableBuilder::visit(const OrExpression* n) {
    n->expr1->Accept(this);
    if (curType != Type(BoolType{})) {
        valExpr = false;
        std::cout << "error: type mismatch.\n";
        errors.push_back("error: type mismatch.\n");
    }
    curType = Type(NoneType{});
    n->expr2->Accept(this);
    if (curType != Type(BoolType{})) {
        valExpr = false;
        std::cout << "error: type mismatch.\n";
        errors.push_back("error: type mismatch.\n");
    }
    curType = Type(BoolType{});
}

void TableBuilder::visit(const RemainExpression* n) {
    n->expr1->Accept(this);
    if (curType != Type(IntType{})) {
        valExpr = false;
        std::cout << "error: type mismatch.\n";
        errors.push_back("error: type mismatch.\n");
    }
    curType = Type(NoneType{});
    n->expr2->Accept(this);
    if (curType != Type(IntType{})) {
        valExpr = false;
        std::cout << "error: type mismatch.\n";
        errors.push_back("error: type mismatch.\n");
    }
    curType = Type(IntType{});
}

void TableBuilder::visit(const ArrayExpression* n) {
    n->expr1->Accept(this);
    if (curType != Type(IntArrType{})) {
        valExpr = false;
        std::cout << "error: type mismatch.\n";
        errors.push_back("error: type mismatch.\n");
    }
    curType = Type(NoneType{});
    n->expr2->Accept(this);
    if (curType != Type(IntType{})) {
        valExpr = false;
        std::cout << "error: type mismatch.\n";
        errors.push_back("error: type mismatch.\n");
    }
    curType = Type(IntType{});
}

void TableBuilder::visit(const LengthExpression* n) {
    n->expr->Accept(this);
    if (curType != Type(IntArrType{})) {
        valExpr = false;
        std::cout << "error: type mismatch.\n";
        errors.push_back("error: type mismatch.\n");
    }
    curType = Type(IntType{});
}

void TableBuilder::visit(const MethodExpression* n) {
    n->class_name->Accept(this);
    if (curType == Type(IntType{}) || curType == Type(NoneType{}) || curType == Type(IntArrType{}) || curType == Type(BoolType{})) {
        std::cout << "error: calling a method from a primitive type.\n";
        errors.push_back("error: calling a method from a primitive type.\n");
        valExpr = false;
        return;
    }
    if (curClass->methods.find(dynamic_cast<Identifier*>(n->method.get())->name) == curClass->methods.end()) {
        valExpr = false;
        std::cout << "error: Method " << dynamic_cast<Identifier*>(n->method.get())->name->getString() << " doesn't exist.\n";
        errors.push_back("error: Method doesn't exist.\n");
        return;
    }
    auto met = curClass->methods[dynamic_cast<Identifier*>(n->method.get())->name];
    if (met->args.size() != n->params->size()) {
        valExpr = false;
        std::cout << "error: Wrong args.\n";
        errors.push_back("error: Wrong args.\n");
        return;
    }
    curType = *(met->type);

}

void TableBuilder::visit(const Integer*) {
    curType = Type(IntType{});
}

void TableBuilder::visit(const Bool*) {
    curType = Type(BoolType{});
}

void TableBuilder::visit(const IdentExpression* n) {
    n->ident->Accept(this);
}

void TableBuilder::visit(const This*) {
    curType = Type(ClassType{curClass->name});
}

void TableBuilder::visit(const NewArrExpression* n) {
    n->expr->Accept(this);
    if (curType != Type(IntType{})) {
        valExpr = false;
        std::cout << "error: type mismatch.\n";
        errors.push_back("error: type mismatch.\n");
    }
    curType = Type(IntArrType{});
}

void TableBuilder::visit(const NewExpression* n) {
    n->ident->Accept(this);
    if (curType == Type(IntType{}) || curType == Type(NoneType{}) || curType == Type(IntArrType{}) || curType == Type(BoolType{})) {
        valExpr = false;
    }
}

void TableBuilder::visit(const NotExpression* n) {
    n->expr->Accept(this);
    if (curType != Type(BoolType{})) {
        valExpr = false;
        std::cout << "error: type mismatch in not.\n";
        errors.push_back("error: type mismatch.\n");
    }
    curType = Type(BoolType{});
}
void TableBuilder::visit(const Expression* n)  {
    n->expr->Accept(this);
}

void TableBuilder::visit(const Identifier* n)  {
    if (curClass->vars.find(n->name) != curClass->vars.end()) {
        auto var = curClass->vars[n->name];
        curType = *(var->type);
    }
    else if (curMethod->locals.find(n->name) != curMethod->locals.end()) {
        auto var = curMethod->locals[n->name];
        curType = *(var->type);
    }
    else if (curMethod->args.find(n->name) != curMethod->args.end()) {
        auto var = curMethod->args[n->name];
        curType = *(var->type);
    }
    else if (table->classes.find(n->name) != table->classes.end()) {
        auto cl = table->classes[n->name];
        curType = Type(ClassType{cl->name});
        curClass = cl;
    }
    else {
        valExpr = false;
        std::cout << "error: Identifier "<< n->name->getString() << " doesn't exist.\n";
        errors.push_back("error: Identifier doesn't exist.\n");
    }
}
