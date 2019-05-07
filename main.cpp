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

//#include "IRTree_canonical/Translator.h"
//#include "IRTree_canonical/IRPrinter.h"
#include "IRTree/canonizers/CallCanon.h"
#include "IRTree/canonizers/ESeqCanon.h"

extern int yyparse(Goal *goal);

extern void yyerror(Goal *goal, const char *msg);

extern FILE *yyin;

int main(int argc, char **argv) {
    FILE *myfile;

    if (argc == 1) {
        myfile = fopen("input.txt", "r");
    } else {
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

        // Build IRT
        Translator translator(table);
        translator.visit(goal);

        // Print IRT
        for (auto &codeFragment : translator.fragments) {
            IRPrinter printer("output" + codeFragment.first + ".dot");
            codeFragment.second.body->Accept(&printer);
        }



        // Canonize IRT
        //std::map<std::string, CodeFragment> codeFragments;
        //codeFragments = std::move( translator.fragments);

        for (auto &codeFragment : translator.fragments) {
            std::cout << "new code fragment!\n";
            IRT::CallCanon callCanonizator;
            codeFragment.second.body->Accept( &callCanonizator );
            std::cout << "Start canonize call!\n";
            codeFragment.second.rootCanonIRT = callCanonizator.CanonicalTree();
            std::cout << "Finish canonize call!\n";


            IRT::ESeqCanon eseqCanonizator;
            std::cout << "ESeqCanon inited!\n";
            codeFragment.second.rootCanonIRT->Accept( &eseqCanonizator );
            std::cout << "Start canonize ESeq!\n";
            codeFragment.second.rootCanonIRT = eseqCanonizator.CanonicalTree();
            std::cout << "Finish canonize ESeq!\n";
        }
//
        //draw Canonized IRT
        for (auto &codeFragment : translator.fragments) {
            IRPrinter printer("output" + codeFragment.first + "_canonized.dot");
            codeFragment.second.rootCanonIRT->Accept(&printer);
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
