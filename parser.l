%option noyywrap
%option outfile="parser.lexer.c" header-file="parser.lexer.h"

%{
#include <string>
#include <iostream>
#include "parser.tab.h"
using namespace std;
%}

%%
[ \t]; // Ignore whitespace, tabs
[\n] {return T_NEWLINE;}


"+" {return T_PLUS;}
"-" {return T_MINUS;}
"*" {return T_MULT;}
"\\" {return T_DIVIDE;}
"%" {return T_REMAIN;}
"&&" {return T_ADD;}
"||" {return T_OR;}
"<" {return T_LESS;}
"!" {return T_NOT;}

"(" {return T_R_LEFT;}
")" {return T_R_RIGHT;}
"{" {return T_F_LEFT;}
"}" {return T_F_RIGHT;}
"[" {return T_Q_LEFT;}
"]" {return T_Q_RIGHT;}
"." {return T_DOT;}
"," {return T_COMMA;}
";" {return T_SCOLON;}
"=" {return T_EQ;}

"int" {return T_INT;}
"boolean" {return T_BOOL;}

"true" {return T_TRUE;}
"false" {return T_FALSE;}

"this" {return T_THIS;}
"new" {return T_NEW;}
"class" {return T_CLASS;}
"public" {return T_PUBLIC;}
"private" {return T_PRIVATE;}
"static" {return T_STATIC;}
"void" {return T_VOID;}
"extends" {return T_EXTENDS;}

"if" {return T_IF;}
"else" {return T_ELSE;}
"while" {return T_WHILE;}

"System.out.println" {return T_PRINT;}

[0-9]+ {yylval.ival = atoi(yytext); return T_NUM;}
[a-zA-Z0-9]+ {yylval.sval = strdup(yytext); return T_STRING;}

%%