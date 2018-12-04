clear;
flex lexer.l;
bison -dv parser.y;
g++ lex.yy.c parser.tab.c -o prog;
./prog testLUNES.txt
