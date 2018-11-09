all: parser

parser.tab.c parser.tab.h: parser.y
	bison -d -v -l parser.y

parser.lexer.c parser.lexer.h: parser.l parser.tab.c parser.tab.h
	flex parser.l

parser: parser.lexer.c parser.lexer.h parser.tab.c parser.tab.h
	g++ parser.tab.c parser.lexer.c AST/Identifier.c AST/Expression.c AST/Statement.c AST/Type.c AST/VarDeclaration.c -lfl -o parser -std=c++11

clean:
	rm -f parser parser.lexer.c parser.lexer.h parser.tab.c parser.tab.h parser.output