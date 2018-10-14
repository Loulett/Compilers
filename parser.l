%option noyywrap
%option outfile="minijava.lexer.cpp" header-file="minijava.lexer.h"

%{
#include <iostream>
using namespace std;
extern int yylex();
%}

%%
[ \t\n]; // Ignore whitespace, tabs
[\n] {cout << endl;}

"+" {cout << "T_PLUS";}
"-" {cout << "T_MINUS";}
"*" {cout << "T_MULT";}
"\\" {cout << "T_DIVIDE";}
"%" {cout << "T_REMAIN";}
"&&" {cout << "T_AND";}
"||" {cout << "T_OR";}
"<" {cout << "T_LESS";}
"!" {cout << "T_NOT";}

"(" {cout << "T_R_LEFT";}
")" {cout << "T_R_RIGHT";}
"{" {cout << "T_F_LEFT";}
"}" {cout << "T_F_RIGHT";}
"[" {cout << "T_Q_LEFT";}
"]" {cout << "T_Q_RIGHT";}
"." {cout << "T_DOT";}
"," {cout << "T_COMMA";}
";" {cout << "T_SCOLON";}
"=" {cout << "T_EQ";}

"int" {cout << "T_INT";}
"boolean" {cout << "T_BOOL";}

"true" {cout << "T_TRUE";}
"false" {cout << "T_FALSE";}

"this" {cout << "T_THIS";}
"new" {cout << "T_NEW";}
"class" {cout << "T_CLASS";}
"public" {cout << "T_PUBLIC";}
"private" {cout << "T_PRIVATE";}
"static" {cout << "T_STATIC";}
"void" {cout << "T_VOID";}
"extends" {cout << "T_EXTENDS";}

"if" {cout << "T_IF";}
"else" {cout << "T_ELSE";}
"while" {cout << "T_WHILE";}

"System.out.println" {cout << "T_PRINT";}

[0-9]+ {cout << "T_INT: " << atoi(yytext);}
[a-zA-Z0-9]+ {cout << "T_STRING: " << yytext;}

%%

int main(int, char**) {
	FILE *myfile = fopen("input.txt", "r");
	yyin = myfile;
	yylex();
}