all: utAtom

utAtom: mainAtom.o
ifeq (${OS}, Windows_NT)
	g++ -o hw3 mainAtom.o -lgtest 
else
	g++ -o hw3 mainAtom.o -lgtest -lpthread
endif
mainAtom.o: mainAtom.cpp atom.h utStruct.h struct.h
	g++ -std=gnu++0x -c mainAtom.cpp

utVariable: mainVariable.o
		g++ -o utVariable mainVariable.o  -lgtest -lpthread
mainVariable.o: mainVariable.cpp utVariable.h variable.h
		g++ -std=gnu++0x -c mainVariable.cpp

clean:
	rm -f *.o madRace utAtom utVariable
stat:
	wc *.h *.cpp

test:
	make clean
	make 
	./hw3

