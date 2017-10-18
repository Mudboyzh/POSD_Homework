INC_DIR = include

all: hw3

hw3: main.o term.o atom.o number.o variable.o struct.o
ifeq (${OS}, Windows_NT)
	g++ -o hw3 main.o term.o atom.o number.o variable.o struct.o -lgtest
else
	g++ -o hw3 main.o term.o atom.o number.o variable.o struct.o -lgtest -lpthread
endif
	
main.o: main.cpp utVariable.h utStruct.h
	g++ -std=gnu++0x -c main.cpp
term.o: term.cpp term.h
	g++ -std=gnu++0x -c term.cpp

atom.o: atom.cpp atom.h
	g++ -std=gnu++0x -c atom.cpp

number.o: number.cpp number.h
	g++ -std=gnu++0x -c number.cpp

variable.o: variable.cpp variable.h
	g++ -std=gnu++0x -c variable.cpp

struct.o: struct.h
	g++ -std=gnu++0x -c struct.cpp

clean:	
ifeq (${OS}, Windows_NT)
	del *.o *.exe
else
	rm -f *.o hw3
endif