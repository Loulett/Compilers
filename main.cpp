#include "parser.tab.h"
#include "AST/Goal.h"
#include "Printer.h"
#include "Printer_graph.h"
#include "SymbolTable/Table.h"
#include "SymbolTable/TableBuilder.h"
#include "SymbolTable/Symbol.h"
#include "IRTree/Translator.h"
#include "IRTree/IRPrinter.h"
#include <cstdio>
#include <iostream>


extern int yyparse(Goal *goal);

extern void yyerror(Goal *goal, const char *msg);

extern FILE *yyin;

int main(int argc, char **argv) {
    FILE *myfile;

    // std::cout.

    if (argc == 1) {
        //std::cout << "Reading data from file input.txt\n";
        myfile = fopen("input.txt", "r");
    } else {
        //std::cout << "Reading data from file " << argv[1] << "\n";
        myfile = fopen(argv[1], "r");
    }
    yyin = myfile;
    Goal *goal = nullptr;
    Table *table = nullptr;
    try {
        yyparse(&goal);
        Printer_graph tree_printer("output.dot");
        tree_printer.visit(goal);

        TableBuilder table_builder;
        table = table_builder.buildTable(goal);
        table_builder.printErrors();

        Translator translator(table);
        translator.visit(goal);

        for (auto &codeFragment : translator.fragments) {
            IRPrinter printer("output" + codeFragment.first + ".dot");
            codeFragment.second.body->Accept(&printer);
        }
    } catch (...) {
        fclose(myfile);
        delete goal;
        delete table;
        return 0;
    }

    fclose(myfile);
    delete goal;
    delete table;
    std::cout << "success" << std::endl;
    return 0;
}
