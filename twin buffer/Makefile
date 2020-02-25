CC=gcc
INCLUDES=lexer.h parser.h lexerDef.h parserDef.h

stage1exe: driver.o lexer.o parserdemo.o
	$(CC) -o $^ $@

*.o: *.c $(INCLUDES)
	$(CC) -c $@