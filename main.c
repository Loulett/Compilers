#include "parser.tab.h"
#include "AST/Goal.h"
#include "Printer.h"
#include <cstdio>

extern int yyparse(Goal* goal);
extern void yyerror(Goal* goal, const char* msg);
extern FILE *yyin;

int main(int, char**) {
	FILE* myfile = fopen("input.txt", "r");
	FILE* outfile = fopen("output.txt", "w");
	yyin = myfile;
	Goal* goal = nullptr;
	yyparse(&goal);

    Printer tree_printer(outfile);
	tree_printer.visit(goal);
	
	fclose(myfile);
	fclose(outfile);
	delete goal;
}