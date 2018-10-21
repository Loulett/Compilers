# Compilers

To compile:
```
make
```

It will compile bison (and add files `parser.tab.c`, `parser.tab.h`), flex (and add files `parser.lexer.h`, `parser.lexer.c`) and compile them to `parser`.

To run:
```
./parser
```

Currently it just reads `input.txt` and prints out contents to list of tokens.

# Done
* Add flex
* Add bison

# TODO
* Add autotests
* Add grammar