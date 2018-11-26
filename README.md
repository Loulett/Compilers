# Compilers

To compile:
```
make
```

It will compile bison (and add files `parser.tab.c`, `parser.tab.h`), flex (and add files `parser.lexer.h`, `parser.lexer.c`), files for AST and compile them to file `parser`. It will also create file `parser.output` with final-state machine created from bison's grammar.

To run:
```
./parser
```

Currently it reads `input.txt`, parse it through final-state machine, create AST and draw in into `output.dot` file.

To show graph: <br />
```asm
sudo apt install xdot
xdot output.dot
```

To clean:
```
make clean
```

It will delete files `parser.tab.c`, `parser.tab.h`, `parser.lexer.h`, `parser.lexer.c`, `parser`, `parser.output`, `output.dot`.

# TODO
## Done
* Add flex
* Add bison
* Add grammar
* Add AST
* Add visitor
* Add printer
* Add AST visualization

## TODO
* Add autotests
* Add error checks for flex
* Add error checks for bison
* Add symbols table