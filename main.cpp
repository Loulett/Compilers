#include "parser.tab.h"
#include "AST/Goal.h"
#include "Printer.h"
#include "Printer_graph.h"
#include "SymbolTable/Table.h"
#include "SymbolTable/TableBuilder.h"
#include "SymbolTable/Symbol.h"
#include <cstdio>
#include <iostream>

extern int yyparse(Goal* goal);
extern void yyerror(Goal* goal, const char* msg);
extern FILE *yyin;

int main(int, char**) {
	FILE* myfile = fopen("input.txt", "r");
	yyin = myfile;
	Goal* goal = nullptr;
	Table* table = nullptr;
	try {
		yyparse(&goal);
		Printer_graph tree_printer("output.dot");
		tree_printer.visit(goal);

		TableBuilder table_builder;
		table = table_builder.buildTable(goal);
		table_builder.printErrors();
	} catch(...) {
		fclose(myfile);
		delete goal;
		delete table;
		return 0;
	}

	fclose(myfile);
	delete goal;
	delete table;
	return 0;
}
