%option noyywrap
%option outfile="minijava.lexer.cpp" header-file="minijava.lexer.h"

%{
#include <iostream>
#include <string>
using namespace std;
extern int yylex();

size_t line_index = 0;
size_t char_index = 0;

void print_token(string token_name) {
	cout << token_name << " " << line_index << " " << char_index << " " << char_index + yyleng -1 << " ";
	char_index += yyleng;
}
%}

%%
[ \t\n]; // Ignore whitespace, tabs
[\n] {cout << endl; line_index++; char_index = 0;}

"+" {print_token("T_PLUS");}
"-" {print_token("T_MINUS");}
"*" {print_token("T_MULT");}
"\\" {print_token("T_DIVIDE");}
"%" {print_token("T_REMAIN");}
"&&" {print_token("T_AND");}
"||" {print_token("T_OR");}
"<" {print_token("T_LESS");}
"!" {print_token("T_NOT");}

"(" {print_token("T_R_LEFT");}
")" {print_token("T_R_RIGHT");}
"{" {print_token("T_F_LEFT");}
"}" {print_token("T_F_RIGHT");}
"[" {print_token("T_Q_LEFT");}
"]" {print_token("T_Q_RIGHT");}
"." {print_token("T_DOT");}
"," {print_token("T_COMMA");}
";" {print_token("T_SCOLON");}
"=" {print_token("T_EQ");}

"int" {print_token("T_INT");}
"boolean" {print_token("T_BOOL");}

"true" {print_token("T_TRUE");}
"false" {print_token("T_FALSE");}

"this" {print_token("T_THIS");}
"new" {print_token("T_NEW");}
"class" {print_token("T_CLASS");}
"public" {print_token("T_PUBLIC");}
"private" {print_token("T_PRIVATE");}
"static" {print_token("T_STATIC");}
"void" {print_token("T_VOID");}
"extends" {print_token("T_EXTENDS");}

"if" {print_token("T_IF");}
"else" {print_token("T_ELSE");}
"while" {print_token("T_WHILE");}

"System.out.println" {print_token("T_PRINT");}

[0-9]+ {cout << "T_INT: " << atoi(yytext); char_index += yyleng;}
[a-zA-Z0-9]+ {cout << "T_STRING: " << yytext; char_index += yyleng;}

%%

int main(int, char**) {
	FILE *myfile = fopen("input.txt", "r");
	yyin = myfile;
	yylex();
}