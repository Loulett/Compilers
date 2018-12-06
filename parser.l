%option noyywrap
%option outfile="parser.lexer.c" header-file="parser.lexer.h"

%{
#include <string>
#include <iostream>
#include "parser.tab.h"
using namespace std;
%}

DIGIT [0-9]
NUM ({DIGIT})+
CHAR [a-zA-Z_]
STRING ({CHAR})+
IDENT {STRING}({STRING}|{NUM})*
COMMENT "//".*\n


%%
[ \t\n]+ ; // Ignore whitespace, tabs, new lines
{COMMENT} ; // Ignore comments


"+" {return T_PLUS;}
"-" {return T_MINUS;}
"*" {return T_MULT;}
"%" {return T_REMAIN;}
"&&" {return T_AND;}
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
"String" {return T_STRING;}

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
"main" {return T_MAIN;}
"return" {return T_RETURN;}

"if" {return T_IF;}
"else" {return T_ELSE;}
"while" {return T_WHILE;}

"System.out.println" {return T_PRINT;}
".length" {return T_LENGTH;}

{IDENT} {yylval.sval = strdup(yytext); return T_IDENT;}
{NUM} {yylval.ival = atoi(yytext); return T_NUM;}

. {cout << "Invalid syntax" << yytext << "\n";}

%%