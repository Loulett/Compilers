all: parser

parser.tab.c parser.tab.h: parser.y
	bison -d -v -l parser.y

parser.lexer.c parser.lexer.h: parser.l parser.tab.c parser.tab.h
	flex parser.l

DEBUG_FLAGS=-fsanitize=address,undefined -g

WARNINGS = -Reverything -Weverything -Wno-c++98-compat -Wno-c++98-compat-pedantic \
		   -Wno-global-constructors -Wno-gnu-zero-variadic-macro-arguments -Wno-missing-prototypes \
		   -Wno-missing-variable-declarations -Wno-shadow-field-in-constructor \
		   -Wno-weak-vtables -Wno-return-std-move-in-c++11 \
		   \
		   -Wno-padded -Wno-exit-time-destructors

CXXFLAGS=-std=c++17 #${DEBUG_FLAGS}

AST=AST/Identifier.cpp AST/Expression.cpp AST/Statement.cpp AST/Type.cpp AST/VarDeclaration.cpp AST/MethodDeclaration.cpp AST/ClassDeclaration.cpp AST/MainClass.cpp AST/Goal.cpp

PRINTER=Printer_graph.cpp #Printer.cpp

SYMBOLTABLE=SymbolTable/Symbol.cpp SymbolTable/TableBuilder.cpp SymbolTable/ClassInfo.cpp SymbolTable/MethodInfo.cpp SymbolTable/VariableInfo.cpp

parser.tab.o: parser.tab.c parser.tab.h
	clang++ ${CXXFLAGS} -Wno-deprecated -c parser.tab.c -o parser.tab.o

parser.lexer.o: parser.lexer.c parser.lexer.h
	clang++ ${CXXFLAGS} -Wno-deprecated -c parser.lexer.c -o parser.lexer.o

parser: parser.lexer.o parser.tab.o main.cpp ${AST} ${PRINTER} ${SYMBOLTABLE}
	clang++ ${CXXFLAGS} ${WARNINGS} main.cpp parser.tab.o parser.lexer.o ${AST} ${PRINTER} ${SYMBOLTABLE} -o parser

clean:
	rm -f parser parser.lexer.c parser.lexer.h parser.tab.c parser.tab.h parser.output output.dot *.o
