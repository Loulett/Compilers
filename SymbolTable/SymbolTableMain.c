#include "SymbolTableMain.h"

SymbolTableMain::SymbolTableMain()
        : table( new Table ), curClass( nullptr ), curMethod( nullptr ), curVariable( nullptr )
{
}

bool SymbolTableMain::hasClass(Symbol* className)
{
    return table->classes.find( className ) != table->classes.end();
}

void SymbolTableMain::visit( const Goal* n )
{
    n->mainClass->Accept( this );
    for ( auto& classDeclaration : *n->class_declarations ) {
        classDeclaration->Accept( this );
    }

    for ( auto& classDeclaration : *n->class_declarations ) {
        // рассматриваем класс curClass
        curClass = table->classes[classDeclaration.get()->class_name->value.get()];
        // проходимся по всем существующим классам
        for (auto& clazz : table->classes) {
            // если у класса родитель curClass, записываем эту инфу
            if (clazz.second->parent != nullptr && clazz.second->parent == curClass->name) {
                clazz.second->parentInfo = curClass;
                //проходимся по всем полям класса, являющ потомком curClass
                for ( auto& var : clazz.second->fields ) {
                    //если поле curClass является классом-потомком curClass
                    if ( curClass->HasField( var.second->symbol ) ) {
                        //выдаём ошибку
                        std::string error = string_format(
                                "Variable %s was already declared as field of class %s.\n",
                                var.second->symbol->String().c_str(),
                                clazz.second->name->String().c_str());
                        errors.push_back( error );
                    }
                }
                //проходимся по всем методам класса, являющ потомком curClass
                for ( auto& met : clazz.second->methods ) {
                    if ( curClass->HasMethod( met.second->name ) ) {
                        //проверка переопределения
                        auto findedMethod = curClass->GetMethod( met.second->name );
                        if ( ( met.second->retType->type != findedMethod->retType->type ) ||
                             ( findedMethod->args.size() != met.second->args.size() ) ) {
                            std::string error = string_format(
                                    "Method %s was already declared in class %s.\n",
                                    met.second->name->String().c_str(),
                                    curClass->name->String().c_str());
                            errors.push_back(error);
                        } else if ( findedMethod->args.size() == met.second->args.size() ) {
                            for (auto arg1 = findedMethod->args.begin(), arg2 = met.second->args.begin();
                                 arg1 != findedMethod->args.end(); arg1++, arg2++) {
                                if ( ( (*arg1).second->type->type != (*arg2).second->type->type ) ||
                                     ( ( (*arg1).second->type->type == Type::TYPE::CUSTOM ) &&
                                       ( table->classes[(*arg1).second->type->name.operator*().value.get()] !=
                                         table->classes[(*arg2).second->type->name.operator*().value.get()] ) ) ) {
                                    std::string error = string_format(
                                            "Method %s was already declared in class %s.\n",
                                            met.second->name->String().c_str(),
                                            curClass->name->String().c_str());
                                    errors.push_back(error);
                                    break;
                                }
                            }
                        }
                    }
                    //проходимся по атрибутам метода класса-потомка curClass
                    for ( auto& arg : met.second->args ) {
                        //проверка атрибутов на валидность
                        if ( arg.second->type->type == Type::TYPE::CUSTOM &&
                             table->classes.find( arg.second->type->name.operator*().value.get() ) == table->classes.end() ) {
                            std::string
                                    error = string_format( "The type of one argument %s does not declared yet",
                                                           (*(arg.second->type->name)).value.get() );
                            errors.push_back( error );
                        }
                    }
                }
            }
        }

        curClass = 0;
    }
    //проходимся по всем классам
    for ( auto& classDeclaration : *n->class_declarations ) {
        curClass = table->classes[classDeclaration.get()->id->value.get()];
        // иесли родитель класса есть, но не объявлен
        if (curClass->parent != nullptr && curClass->parentInfo == nullptr) {
            std::string error = string_format( "Class %s extends at class %s which wasn't declared\n",
                                               curClass->name->String().c_str(),
                                               curClass->parent->String().c_str());
            errors.push_back( error );
        }

        curClass = 0;
    }
}

void SymbolTableMain::visit( const MainClass* n )
{
    //разбираем MainClass из AST
    curClass = new ClassInfo;
    curClass->name = n->class_name->value.get();

    if ( hasClass(curClass->name) ) {
        std::string error = string_format( "Class %s was already declared\nTrying to redeclare at (line %d)\n",
                                           curClass->name->String().c_str(),
                                           n->fstLine );
        errors.push_back( error );
    }
    //записываем в таблицу класс
    table->classes[curClass->name] = curClass;
    //начинаем разбирать класс по частям

    table->classes[curClass->name]->methods[n->mainId->value.get()] = mainMethod;
    curClass = 0;
}

void SymbolTableMain::visit( const ClassDeclaration* n )
{
    curClass = new ClassInfo;
    curClass->name = n->class_name->value.get();
    // добавляем инфу о р. классах
    if ( n->extends_class_name == nullptr ) {
        curClass->parent = nullptr;
        curClass->parentInfo = nullptr;
    } else {
        curClass->parent = n->extends_class_name->value.get();
        curClass->parentInfo = nullptr;
    }

    if ( hasClass(curClass->name) ) {
        std::string error = string_format( "Class %s was already declared\nTrying to redeclare at (line %d)\n",
                                           curClass->name->String().c_str(),
                                           n->fstLine );
        errors.push_back( error );
    }
    table->classes[curClass->name] = curClass;

    for ( auto& varDeclaration: *(n->vars)) {
        varDeclaration->Accept( this );
    }
    for ( auto& methodDeclaration: *(n->methods)) {
        methodDeclaration->Accept( this );
    }
    //проверить память
    curClass = 0;
}

void SymbolTableMain::visit( const VarDeclaration* n )
{
    //аналогично
    // узнать о сущноси из дерева
    curVariable = new VarInfo;
    curVariable->type = n->type;
    curVariable->symbol = n->name->value.get();
    //чекнуть ошибки
    if ( curMethod != 0 ) {
        if ( curMethod->locals.find( curVariable->symbol ) != curMethod->locals.end()) {
            std::string error = string_format(
                    "Variable %s was already declared as local variable of method %s.\n Trying to redeclare at (line %d)\n",
                    curVariable->symbol->String().c_str(),
                    curMethod->name->String().c_str(),
                    n->fstLine );
            errors.push_back( error );
        }
        curMethod->locals[curVariable->symbol] = curVariable;
    } else {

        if ( curClass->HasField( curVariable->symbol ) ) {
            std::string error = string_format(
                    "Variable %s was already declared as field of class %s.\n Trying to redeclare at (line %d)\n",
                    curVariable->symbol->String().c_str(),
                    curClass->name->String().c_str(),
                    n->fstLine );
            errors.push_back( error );
        }
        //занести в таблицу
        curClass->fields[curVariable->symbol] = curVariable;
    }
    curVariable = 0;
}

void SymbolTableMain::visit( const Argument* n )
{
    curVariable = new VarInfo();
    curVariable->type = n->type;
    curVariable->symbol = n->name->value.get();

    if ( curMethod->args.find( curVariable->symbol ) != curMethod->args.end()) {
        std::string error = string_format(
                "Variable %s was already declared as argument of method %s.\n Trying to redeclare at (line %d)\n",
                curVariable->symbol->String().c_str(),
                curMethod->name->String().c_str(),
                n->fstLine );
        errors.push_back( error );
    }
    curMethod->args[curVariable->symbol] = curVariable;
}

void SymbolTableMain::visit( const MethodDeclaration* n )
{
    curMethod = new MethodInfo;
    curMethod->name = n->name->value.get();
    curMethod->retType = n->return_type;

    if ( curClass->HasMethod( curMethod->name ) ) {
        auto findedMethod = curClass->GetMethod( curMethod->name );
        if ( ( curMethod->retType->type != findedMethod->retType->type ) ||
             ( findedMethod->args.size() != n->args->size() ) ) {
            std::string error = string_format(
                    "Method %s was already declared in class %s.\n Trying to redeclare at (line %d)\n",
                    curMethod->name->String().c_str(),
                    curClass->name->String().c_str(),
                    n->fstLine);
            errors.push_back(error);
        } else if ( findedMethod->args.size() == n->args->size() ) {
            int i = 0;
            for (auto &arg : findedMethod->args) {
                if ( ( (*(*(n->args))[i]).type->type != arg.second->type->type) ||
                     (( arg.second->type->type == Type::TYPE::CUSTOM ) &&
                      ( table->classes.find(arg.second->type->name.operator*().value.get()) != table->classes.end() ) !=
                      ( table->classes.find((*n->args)[i].operator*().type->name.operator*().value.get() ) != table->classes.end() ) ) )
                    /*if ( table->classes[arg.second->type->name.operator*().value.get()] !=
                                        table->classes[(*n->arguments)[i].operator*().type->name.operator*().value.get()] ) */{
                    std::string error = string_format(
                            "Method %s was already declared in class %s.\n Trying to redeclare at (line %d)\n",
                            curMethod->name->String().c_str(),
                            curClass->name->String().c_str(),
                            n->fstLine);
                    errors.push_back(error);
                    break;
                }
                i++;
            }
        }
    }
    curClass->methods[curMethod->name] = curMethod;

    for ( auto& localVar: *n->vars ) {
        localVar->Accept( this );
    }

    for ( auto& arg: *n->args ) {
        arg->Accept( this );
    }

    curMethod = 0;
}

void SymbolTableMain::visit( const Type* n )
{
    assert( false );
}

void SymbolTableMain::visit( const Statement* n )   //0
{
    assert( false );
}

void SymbolTableMain::visit( const IfStatement* n ) //1
{
    assert( false );
}

void SymbolTableMain::visit( const WhileStatement* n )  //2
{
    assert( false );
}

void SymbolTableMain::visit( const PrintStatement* n )  //3
{
    assert( false );
}

void SymbolTableMain::visit( const AssignmentStatement* n )  //4
{
    assert( false );
}

void SymbolTableMain::visit( const ArrAssignmentStatement* n )  //5
{
    assert( false );
}

void SymbolTableMain::visit( const AndExpression* n )
{
    assert( false );
}
void SymbolTableMain::visit( const LessExpression* n )
{
    assert( false );
}
void SymbolTableMain::visit( const PlusExpression* n )
{
    assert( false );
}
void SymbolTableMain::visit( const MinusExpression* n )
{
    assert( false );
}
void SymbolTableMain::visit( const MultExpression* n )
{
    assert( false );
}
void SymbolTableMain::visit( const RemainExpression* n )
{
    assert( false );
}
void SymbolTableMain::visit( const OrExpression* n )
{
    assert( false );
}
void SymbolTableMain::visit( const ArrayExpression* n )
{
    assert( false );
}
void SymbolTableMain::visit( const LengthExpression* n )
{
    assert( false );
}
void SymbolTableMain::visit( const MethodExpression* n )
{
    assert( false );
}
void SymbolTableMain::visit( const Integer* n )
{
    assert( false );
}
void SymbolTableMain::visit( const Bool* n )
{
    assert( false );
}
void SymbolTableMain::visit( const IdentExpression* n )
{
    assert( false );
}
void SymbolTableMain::visit( const This* n )
{
    assert( false );
}
void SymbolTableMain::visit( const NewArrExpression* n )
{
    assert( false );
}
void SymbolTableMain::visit( const NewExpression* n )
{
    assert( false );
}
void SymbolTableMain::visit( const NotExpression* n )
{
    assert( false );
}
void SymbolTableMain::visit( const Expression* n )
{
    assert( false );
}

void SymbolTableMain::visit( const Identifier* n )
{
    assert( false );
}
