-These commands should be used to execute:
	gcc -c lexer.c 
	gcc -c parserdemo.c
	gcc -c driver.c
	gcc -o stage1exe lexer.o parserdemo.o driver.o
	./stage1exe testcase.txt parsetreeOutFile.txt

	