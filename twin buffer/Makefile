CC=gcc
INCLUDES=lexer.h parser.h lexerDef.h parseDef.h

stage1exe: driver.o lexer.o parserdemo.o
	$(CC) -o stage1exe driver.o lexer.o parserdemo.o $(INCLUDES)

driver.o: driver.c 
	$(CC) -c driver.c

lexer.o: lexer.c 
	$(CC) -c lexer.c

parserdemo.o: parserdemo.c 
	$(CC) -c parserdemo.c		