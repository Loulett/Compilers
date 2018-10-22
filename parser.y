%{
#include <cstdio>
#include <iostream>
#include <string>
using namespace std;

extern int yylex();
extern int yyparse();
extern FILE *yyin;

void yyerror(const string s);
%}

%union {
	int ival;
	char* sval;	
}
%token T_NEWLINE
%token T_PLUS
%token T_MINUS
%token T_MULT
%token T_REMAIN
%token T_AND
%token T_OR
%token T_LESS
%token T_NOT

%token T_R_LEFT
%token T_R_RIGHT
%token T_F_LEFT
%token T_F_RIGHT
%token T_Q_LEFT
%token T_Q_RIGHT
%token T_DOT
%token T_COMMA
%token T_SCOLON
%token T_EQ

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

%token T_PRINT
%token T_LENGTH

%token T_EOF

%token <ival> T_NUM
%token <sval> T_IDENT

%%
parser:
	mainClass classesDeclaration T_EOF {cout << "Start ";}
	;

mainClass:
	T_CLASS identifier T_F_LEFT T_PUBLIC T_STATIC T_VOID T_MAIN T_R_LEFT T_STRING T_Q_LEFT T_Q_RIGHT identifier T_R_RIGHT T_F_LEFT statement T_F_RIGHT T_F_RIGHT {cout << "MainClass ";}
	;

classesDeclaration:
	classDeclaration classesDeclaration {cout << "Class ";}
	| %empty
	;

classDeclaration:
	T_CLASS identifier extends T_F_LEFT varsDeclaration methodsDeclaration T_F_RIGHT {cout << "Class ";}
	;

extends:
	T_EXTENDS identifier {cout << "Extends ";}
	| %empty
	;

varsDeclaration:
	varDeclaration varsDeclaration
	| %empty
	;

varDeclaration:
	type identifier T_SCOLON {cout << "Var ";}
	;

methodsDeclaration:
	methodDeclaration methodsDeclaration
	| %empty
	;

methodDeclaration:
	methodType type identifier T_R_LEFT methodParams T_R_RIGHT T_F_LEFT varsDeclaration statements T_RETURN expression T_SCOLON T_F_RIGHT {cout << "Method ";}
	;

methodType:
	T_PUBLIC {cout << "Public ";}
	| T_PRIVATE {cout << "Private ";}
	;

methodParams:
	type identifier otherParams {cout << "Param ";}
	| %empty
	;

otherParams:
	T_COMMA type identifier otherParams {cout << "Param ";}
	| %empty
	;

statements:
	statement statements
	| %empty
	;

type:
	T_INT T_Q_LEFT T_Q_RIGHT {cout << "Array int ";}
	| T_BOOL {cout << "Bool ";}
	| T_INT {cout << "Int ";}
	| identifier
	;

statement:
	T_F_LEFT statements T_F_RIGHT
	| T_IF T_R_LEFT expression T_R_RIGHT statement T_ELSE statement {cout << "If ";}
	| T_WHILE T_R_LEFT expression T_R_RIGHT statement {cout << "While ";}
	| T_PRINT T_R_LEFT expression T_R_RIGHT T_SCOLON {cout << "Print ";}
	| identifier T_EQ expression T_SCOLON {cout << "Assingment ";}
	| identifier T_Q_LEFT expression T_Q_RIGHT T_EQ expression T_SCOLON {cout << "Array Assignment ";}
	;

expression:
	expression operator expression
	| expression T_Q_LEFT expression T_Q_RIGHT
	| expression T_DOT T_LENGTH {cout << "Length ";}
	| expression T_DOT identifier T_R_LEFT expressions T_R_RIGHT
	| T_NUM {cout << "Int " << $1 << " ";}
	| T_TRUE {cout << "True ";}
	| T_FALSE {cout << "False ";}
	| identifier
	| T_THIS {cout << "This ";}
	| T_NEW T_INT T_Q_LEFT expression T_Q_RIGHT {cout << "New int array ";}
	| T_NEW identifier T_R_LEFT expression T_R_RIGHT {cout << "New ";}
	| T_NOT expression {cout << "Not ";}
	| T_R_LEFT expression T_R_RIGHT
	;

operator:
	T_AND {cout << "And ";}
	| T_LESS {cout << "Less ";}
	| T_PLUS {cout << "Plus ";}
	| T_MINUS {cout << "Minus ";}
	| T_MULT {cout << "Mult ";}
	| T_REMAIN {cout << "Remain ";}
	| T_OR {cout << "Or ";}
	;

expressions:
	expression otherExpressions
	| %empty
	;

otherExpressions:
	T_COMMA expression otherExpressions
	| %empty
	;

identifier:
	T_IDENT {cout << "String " << $1 << " ";}
	;
%%

int main(int, char**) {
	FILE *myfile = fopen("input.txt", "r");
	yyin = myfile;
	yyparse();
}

void yyerror(const string s) {
	cout << "PARSE ERROR " << s << endl;
}