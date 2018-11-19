#include "parser.tab.h"
#include "AST/Goal.h"
#include "Printer.h"
#include "Printer_graph.h"
#include "Printer_graph.c"
#include <cstdio>

extern int yyparse(Goal* goal);
extern void yyerror(Goal* goal, const char* msg);
extern FILE *yyin;

int main(int, char**) {
	FILE* myfile = fopen("input.txt", "r");
//	FILE* outfile = fopen("output.txt", "w");
	FILE* outfile = fopen("output.dot", "w");
	yyin = myfile;
	Goal* goal = nullptr;
	yyparse(&goal);

//    Printer tree_printer(outfile);
//    tree_printer.visit(goal);


    Printer_graph tree_printer(outfile);
	tree_printer.visit(goal);
    tree_printer.~Printer_graph();
	
	fclose(myfile);
	fclose(outfile);
	delete goal;
}