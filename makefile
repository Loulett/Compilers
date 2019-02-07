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

AST=AST/Identifier.c AST/Expression.c AST/Statement.c AST/Type.c AST/VarDeclaration.c AST/MethodDeclaration.c AST/ClassDeclaration.c AST/MainClass.c AST/Goal.c

PRINTER=Printer_graph.c #Printer.c

SYMBOLTABLE=SymbolTable/Symbol.c SymbolTable/TableBuilder.c SymbolTable/ClassInfo.c SymbolTable/MethodInfo.c SymbolTable/VariableInfo.c

parser.tab.o: parser.tab.c parser.tab.h
	clang++ ${CXXFLAGS} -c parser.tab.c -o parser.tab.o

parser.lexer.o: parser.lexer.c parser.lexer.h
	clang++ ${CXXFLAGS} -c parser.lexer.c -o parser.lexer.o

parser: parser.lexer.o parser.tab.o main.c ${AST} ${PRINTER} ${SYMBOLTABLE}
	clang++ ${CXXFLAGS} ${WARNINGS} main.c parser.tab.o parser.lexer.o ${AST} ${PRINTER} ${SYMBOLTABLE} -o parser

clean:
	rm -f parser parser.lexer.c parser.lexer.h parser.tab.c parser.tab.h parser.output output.dot *.o
