# Compilers

To compile:
```
make
```

It will compile bison (and add files `parser.tab.c`, `parser.tab.h`), flex (and add files `parser.lexer.h`, `parser.lexer.c`) and compile them to `parser`. It will also create file `parser.output` with final-state machine created from bison's grammar.

To run:
```
./parser
```

Currently it just reads `input.txt`, parse it through final-state machine and prints out some debug information (e.g. finished rules).

To show graph: <br />
```asm
sudo apt install xdot
xdot output.dot
```
# Done
* Add flex
* Add bison
* Add grammar
* Add AST
* Add visitor
* Add printer
* Add AST visualization

# TODO
* Add autotests
* Add errors