all: parser

minijava.lexer.cpp: parser.l
	flex parser.l

parser: minijava.lexer.cpp
	g++ minijava.lexer.cpp -o parser

clean:
	rm -f parser minijava.lexer.cpp minijava.lexer.h