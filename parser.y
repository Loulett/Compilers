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
%token T_DIVIDE
%token T_REMAIN
%token T_ADD
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

%token T_IF
%token T_ELSE
%token T_WHILE

%token T_PRINT

%token <ival> T_NUM
%token <sval> T_STRING

%%
parser:
	parser T_NUM {cout << "T_INT " << $2 << " ";}
	| parser T_STRING {cout << "T_STRING " << $2 << " ";}
	| parser T_NEWLINE {cout << endl;}
	| parser T_PLUS {cout << "T_PLUS ";}
	| parser T_MINUS {cout << "T_MINUS ";}
	| parser T_MULT {cout << "T_MULT ";}
	| parser T_DIVIDE {cout << "T_DIVIDE ";}
	| parser T_REMAIN {cout << "T_REMAIN ";}
	| parser T_ADD {cout << "T_ADD ";}
	| parser T_OR {cout << "T_OR ";}
	| parser T_LESS {cout << "T_LESS ";}
	| parser T_NOT {cout << "T_NOT ";}
	| parser T_R_LEFT {cout << "T_R_LEFT ";}
	| parser T_R_RIGHT {cout << "T_R_RIGHT ";}
	| parser T_F_LEFT {cout << "T_F_LEFT ";}
	| parser T_F_RIGHT {cout << "T_R_RIGHT ";}
	| parser T_Q_LEFT {cout << "T_S_LEFT ";}
	| parser T_Q_RIGHT {cout << "T_S_RIGHT ";}
	| parser T_DOT {cout << "T_DOT ";}
	| parser T_COMMA {cout << "T_COMMA ";}
	| parser T_SCOLON {cout << "T_SCOLON ";}
	| parser T_EQ {cout << "T_EQ ";}
	| parser T_INT {cout << "T_INT ";}
	| parser T_BOOL {cout << "T_BOOL ";}
	| parser T_TRUE {cout << "T_TRUE ";}
	| parser T_FALSE {cout << "T_FALSE ";}
	| parser T_THIS {cout << "T_THIS ";}
	| parser T_NEW {cout << "T_NEW ";}
	| parser T_CLASS {cout << "T_CLASS ";}
	| parser T_PUBLIC {cout << "T_PUBLIC ";}
	| parser T_PRIVATE {cout << "T_PRIVATE ";}
	| parser T_STATIC {cout << "T_STATIC ";}
	| parser T_VOID {cout << "T_VOID ";}
	| parser T_EXTENDS {cout << "T_EXTEND ";}
	| parser T_IF {cout << "T_IF ";}
	| parser T_ELSE {cout << "T_ELSE ";}
	| parser T_WHILE {cout << "T_WHILE ";}
	| parser T_PRINT {cout << "T_PRINT ";}
	| T_NUM {cout << "INT " << $1 << endl;}
	| T_STRING {cout << "STRING " << $1 << endl;}
	| T_NEWLINE {cout << endl;}
	| T_PLUS {cout << "T_PLUS ";}
	| T_MINUS {cout << "T_MINUS ";}
	| T_MULT {cout << "T_MULT ";}
	| T_DIVIDE {cout << "T_DIVIDE ";}
	| T_REMAIN {cout << "T_REMAIN ";}
	| T_ADD {cout << "T_ADD ";}
	| T_OR {cout << "T_OR ";}
	| T_LESS {cout << "T_LESS ";}
	| T_NOT {cout << "T_NOT ";}
	| T_R_LEFT {cout << "T_R_LEFT ";}
	| T_R_RIGHT {cout << "T_R_RIGHT ";}
	| T_F_LEFT {cout << "T_F_LEFT ";}
	| T_F_RIGHT {cout << "T_R_RIGHT ";}
	| T_Q_LEFT {cout << "T_S_LEFT ";}
	| T_Q_RIGHT {cout << "T_S_RIGHT ";}
	| T_DOT {cout << "T_DOT ";}
	| T_COMMA {cout << "T_COMMA ";}
	| T_SCOLON {cout << "T_SCOLON ";}
	| T_EQ {cout << "T_EQ ";}
	| T_INT {cout << "T_INT ";}
	| T_BOOL {cout << "T_BOOL ";}
	| T_TRUE {cout << "T_TRUE ";}
	| T_FALSE {cout << "T_FALSE ";}
	| T_THIS {cout << "T_THIS ";}
	| T_NEW {cout << "T_NEW ";}
	| T_CLASS {cout << "T_CLASS ";}
	| T_PUBLIC {cout << "T_PUBLIC ";}
	| T_PRIVATE {cout << "T_PRIVATE ";}
	| T_STATIC {cout << "T_STATIC ";}
	| T_VOID {cout << "T_VOID ";}
	| T_EXTENDS {cout << "T_EXTEND ";}
	| T_IF {cout << "T_IF ";}
	| T_ELSE {cout << "T_ELSE ";}
	| T_WHILE {cout << "T_WHILE ";}
	| T_PRINT {cout << "T_PRINT ";}
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