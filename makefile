all: parser

parser.tab.c parser.tab.h: parser.y
	bison -d -v -l parser.y

parser.lexer.c parser.lexer.h: parser.l parser.tab.c parser.tab.h
	flex parser.l

FLAGS=-fsanitize=address,undefined -g 

CXXFLAGS=-std=c++11 ${FLAGS}

AST=AST/Identifier.c AST/Expression.c AST/Statement.c AST/Type.c AST/VarDeclaration.c AST/MethodDeclaration.c AST/ClassDeclaration.c AST/MainClass.c AST/Goal.c

PRINTER=Printer.c Printer_graph.c

SYMBOLTABLE=SymbolTable/Symbol.c

parser: parser.lexer.c parser.lexer.h parser.tab.c parser.tab.h main.c
	g++ ${CXXFLAGS} main.c parser.tab.c parser.lexer.c ${AST} ${PRINTER} ${SYMBOLTABLE} -o parser

clean:
	rm -f parser parser.lexer.c parser.lexer.h parser.tab.c parser.tab.h parser.output output.dot