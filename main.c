#include "parser.tab.h"
#include "AST/Goal.h"

extern int yyparse(Goal* goal);
extern void yyerror(Goal* goal, const char* msg);
extern FILE *yyin;

int main(int, char**) {
	FILE *myfile = fopen("input.txt", "r");
	yyin = myfile;
	Goal* goal = nullptr;
	yyparse(goal);
}