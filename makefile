Sem:  	grammar.y text.flex
	bison --report=all --report-file=report -b grammar -d grammar.y --debug
	flex text.flex
	gcc -o Sem.o structs.h declarations.c xml.c createTree.c treePrint.c treePrintDot.c  main.c grammar.tab.c lex.yy.c -lfl
