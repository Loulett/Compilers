%{
#include <cstdio>
#include <iostream>
#include <string>
#include <utility>
#include <memory>
#include "parser.tab.h"
using namespace std;

extern int yylex();
extern int yyparse(Goal** goal);
extern FILE *yyin;

void yyerror(Goal** goal, const char* s);
%}

%code requires {
#include "AST/INode.h"
#include "AST/Identifier.h"
#include "AST/Expression.h"
#include "AST/Statement.h"
#include "AST/Type.h"
#include "AST/VarDeclaration.h"
#include "AST/MethodDeclaration.h"
#include "AST/ClassDeclaration.h"
#include "AST/MainClass.h"
#include "AST/Goal.h"
}

%parse-param {Goal** goal}
%define parse.error verbose

%union {
	int ival;
	char* sval;
	IIdentifier* ident;
	IExpression* expr;
	std::vector<std::unique_ptr<IExpression>>* exprs;	
	IStatement* state;
	std::vector<std::unique_ptr<IStatement>>* states;
	IType* type;
	IVarDeclaration* varDecl;
	IMethodDeclaration* methodDecl;
	std::vector<std::unique_ptr<IVarDeclaration>>* vars;
	std::vector<std::pair<std::unique_ptr<IType>, std::unique_ptr<IIdentifier>>>* params;
	IClassDeclaration* classDecl;
	IIdentifier* extends;
	std::vector<std::unique_ptr<IMethodDeclaration>>* methods;
	IMainClass* main;
	IGoal* goal;
	std::vector<std::unique_ptr<IClassDeclaration>>* classes;
}

%left T_PLUS
%left T_MINUS
%left T_MULT
%left T_REMAIN
%left T_AND
%left T_OR
%left T_LESS
%left T_NOT

%left T_R_LEFT
%token T_R_RIGHT
%left T_F_LEFT
%token T_F_RIGHT
%left T_Q_LEFT
%token T_Q_RIGHT
%left T_DOT
%token T_COMMA
%token T_SCOLON
%right T_EQ

%token T_INT
%token T_BOOL
%token T_STRING

%token T_TRUE
%token T_FALSE

%token T_THIS
%token T_NEW
%token T_CLASS
%token T_PUBLIC
%token T_PRIVATE
%token T_STATIC
%token T_VOID
%token T_EXTENDS
%token T_MAIN
%token T_RETURN

%token T_IF
%token T_ELSE
%token T_WHILE

%left T_PRINT
%left T_LENGTH

%token <ival> T_NUM
%token <sval> T_IDENT

%type <ident> identifier
%type <expr> expression
%type <exprs> expressions
%type <state> statement
%type <states> statements
%type <type> type
%type <varDecl> varDeclaration
%type <methodDecl> methodDeclaration
%type <vars> varsDeclaration
%type <params> methodParams
%type <classDecl> classDeclaration
%type <extends> extends
%type <methods> methodsDeclaration
%type <main> mainClass
%type <goal> parser
%type <classes> classesDeclaration


%%
parser:
	mainClass classesDeclaration {
		*goal = new Goal($1, $2);
	}
	;

mainClass:
	T_CLASS identifier T_F_LEFT T_PUBLIC T_STATIC T_VOID T_MAIN T_R_LEFT T_STRING T_Q_LEFT T_Q_RIGHT identifier T_R_RIGHT T_F_LEFT statement T_F_RIGHT T_F_RIGHT {
		$$ = new MainClass($2, $12, $15);
	}
	;

classesDeclaration:
	%empty {
		$$ = new std::vector<std::unique_ptr<IClassDeclaration>>();
	}
	| classesDeclaration classDeclaration {
		$1->push_back(std::unique_ptr<IClassDeclaration>($2));
		$$ = $1;
	}
	;

classDeclaration:
	T_CLASS identifier extends T_F_LEFT varsDeclaration methodsDeclaration T_F_RIGHT {
		$$ = new ClassDeclaration($2, $3, $5, $6);
	}
	;

extends:
	%empty {
		$$ = nullptr;
	}
	| T_EXTENDS identifier {
		$$ = $2;
	}
	;

varsDeclaration:
	%empty {
		$$ = new std::vector<std::unique_ptr<IVarDeclaration>>();
	}
	| varsDeclaration varDeclaration {
		$1->push_back(std::unique_ptr<IVarDeclaration>($2));
		$$ = $1;
	}
	;

varDeclaration:
	type identifier T_SCOLON {
		$$ = new VarDeclaration($1, $2);
		}
	;

methodsDeclaration:
	%empty {
		$$ = new std::vector<std::unique_ptr<IMethodDeclaration>>();
	}
	| methodsDeclaration methodDeclaration {
		$1->push_back(std::unique_ptr<IMethodDeclaration>($2));
		$$ = $1;
	}
	;

methodDeclaration:
	methodType type identifier T_R_LEFT methodParams T_R_RIGHT T_F_LEFT varsDeclaration statements T_RETURN expression T_SCOLON T_F_RIGHT {
		$$ = new MethodDeclaration($2, $3, $5, $8, $9, $11);
	}
	;

methodType:
	T_PUBLIC {}
	| T_PRIVATE {}
	;

methodParams:
	%empty {
		$$ = new std::vector<std::pair<std::unique_ptr<IType>, std::unique_ptr<IIdentifier>>>();
	}
	| type identifier {
		$$ = new std::vector<std::pair<std::unique_ptr<IType>, std::unique_ptr<IIdentifier>>>();
		$$->push_back(std::make_pair(std::unique_ptr<IType>($1), std::unique_ptr<IIdentifier>($2)));
	}
	| methodParams T_COMMA type identifier {
		$$->push_back(std::make_pair(std::unique_ptr<IType>($3), std::unique_ptr<IIdentifier>($4)));
		$$ = $1;
	}
	;

statements:
	%empty {
		$$ = new std::vector<std::unique_ptr<IStatement>>();
		}
	| statement statements {
		$2->insert($2->begin(), std::unique_ptr<IStatement>($1));
		$$ = $2;
		}
	;

type:
	T_INT T_Q_LEFT T_Q_RIGHT {
		$$ = new IntArrayType();
		}
	| T_BOOL {
		$$ = new BoolType();
		}
	| T_INT {
		$$ = new IntType();
		}
	| identifier {
		$$ = new Type($1);
		}
	;

statement:
	T_F_LEFT statements T_F_RIGHT {
		$$ = new Statement($2);
		}
	| T_IF T_R_LEFT expression T_R_RIGHT statement T_ELSE statement {
		$$ = new IfStatement($3, $5, $7);
		}
	| T_WHILE T_R_LEFT expression T_R_RIGHT statement {
		$$ = new WhileStatement($3, $5);
		}
	| T_PRINT T_R_LEFT expression T_R_RIGHT T_SCOLON {
		$$ = new PrintStatement($3);
		}
	| identifier T_EQ expression T_SCOLON {
		$$ = new AssignmentStatement($1, $3);
		}
	| identifier T_Q_LEFT expression T_Q_RIGHT T_EQ expression T_SCOLON {
		$$ = new ArrAssignmentStatement($1, $3, $6);
		}
	;

expressions:
	%empty {
		$$ = new std::vector<std::unique_ptr<IExpression>>();
		}
	| expression {
		$$ = new std::vector<std::unique_ptr<IExpression>>();
		$$->push_back(std::unique_ptr<IExpression>($1));
		}
	| expressions T_COMMA expression {
		$$->push_back(std::unique_ptr<IExpression>($3));
		$$ = $1;
		}
	;

expression:
	expression T_AND expression {
		$$ = new AndExpression($1, $3);
		}
	| expression T_LESS expression {
		$$ = new LessExpression($1, $3);
		}
	| expression T_PLUS expression {
		$$ = new PlusExpression($1, $3);
		}
	| expression T_MINUS expression {
		$$ = new MinusExpression($1, $3);
		}
	| expression T_MULT expression {
		$$ = new MultExpression($1, $3);
		}
	| expression T_REMAIN expression {
		$$ = new RemainExpression($1, $3);
		}
	| expression T_OR expression {
		$$ = new OrExpression($1, $3);
		}
	| expression T_Q_LEFT expression T_Q_RIGHT {
		$$ = new ArrayExpression($1, $3);
		}
	| expression T_LENGTH {
		$$ = new LengthExpression($1);
		}
	| expression T_DOT identifier T_R_LEFT expressions T_R_RIGHT {
		$$ = new MethodExpression($1, $3, $5);
		}
	| T_NUM {
		$$ = new Integer($1);
		}
	| T_TRUE {
		$$ = new Bool(true);
		}
	| T_FALSE {
		$$ = new Bool(false);
		}
	| identifier {
		$$ = new IdentExpression($1);
		}
	| T_THIS {
		$$ = new This();
		}
	| T_NEW T_INT T_Q_LEFT expression T_Q_RIGHT {
		$$ = new NewArrExpression($4);
		}
	| T_NEW identifier T_R_LEFT T_R_RIGHT {
		$$ = new NewExpression($2);
		}
	| T_NOT expression {
		$$ = new NotExpression($2);
		}
	| T_R_LEFT expression T_R_RIGHT {
		$$ = new Expression($2);
		}
	;

identifier:
	T_IDENT {
		$$ = new Identifier($1);
	}
	;
%%

void yyerror(Goal** goal, const char* s) {
	cout << "PARSE ERROR " << s << endl;
}