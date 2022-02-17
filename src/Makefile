CC=g++
CFLAGS=-std=c++11 -c


all: oak

oak: main.o lexer.o 
	$(CC) *.o -o oak

main.o: *.cpp *.h
	$(CC) *.cpp $(CFLAGS)

lexer.o: lexer/*.cpp lexer/*.h
	$(CC) lexer/*.cpp $(CFLAGS)

clean: 
	$(RM) *.o 
	$(RM) oak