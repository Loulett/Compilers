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
	try {
		yyparse(&goal);
	} catch(...) {
		return 0;
	}

    Printer_graph tree_printer("output.dot");
	tree_printer.visit(goal);

	TableBuilder table_builder;
	Table* table = table_builder.buildTable(goal);

	std::cout << "Found " << table_builder.errors.size() << " errors\n";

	for (auto& cl: table->classes) {
		std::cout << "Class: " << cl.first->getString() << "\n";
		if (cl.second->parent != nullptr) {
			std::cout << "Parent: " << cl.second->parent->getString() << "\n";
		}
		else {
			std::cout << "Parent: NONE\n";
		}
		for (auto& var: cl.second->vars) {
			std::cout << "Var: " << var.first->getString() << "\n";
		}
		for (auto& met: cl.second->methods) {
			std::cout << "Method: " << met.first->getString() << "\n";
			for (auto& arg: met.second->args) {
				std::cout << "Arg: " << arg.first->getString() << "\n";
			}
			for (auto& loc: met.second->locals) {
				std::cout << "Local: " << loc.first->getString() << "\n";
			}
		}
	}

	fclose(myfile);
	delete goal;
	delete table;
	return 0;
}
