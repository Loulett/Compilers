#include "parser.tab.h"
#include "AST/Goal.h"
#include "Printer.h"
#include "Printer.c"

extern int yyparse(Goal* goal);
extern void yyerror(Goal* goal, const char* msg);
extern FILE *yyin;

int main(int, char**) {
	FILE* myfile = fopen("input.txt", "r");
	yyin = myfile;
	Goal* goal = nullptr;
	yyparse(goal);

    Printer tree_printer(myfile);
    //Printer tree_printer();
	tree_printer.visit(goal);
}