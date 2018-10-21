all: parser

parser.tab.c parser.tab.h: parser.y
	bison -d parser.y

parser.lexer.c parser.lexer.h: parser.l parser.tab.c parser.tab.h
	flex parser.l

parser: parser.lexer.c parser.lexer.h parser.tab.c parser.tab.h
	g++ parser.tab.c parser.lexer.c -lfl -o parser

clean:
	rm -f parser parser.lexer.c parser.lexer.h parser.tab.c parser.tab.h