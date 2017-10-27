all: madRace utAtom utVariable utScanner

madRace: mainMadRace.o
	g++ -o madRace mainMadRace.o -lgtest 
mainMadRace.o: mainMadRace.cpp madRace.h utMadRace.h
	g++ -std=c++0x -c mainMadRace.cpp

utAtom: mainAtom.o atom.o 
	g++ -o hw4 mainAtom.o atom.o -lgtest 
mainAtom.o: mainAtom.cpp utAtom.h atom.h utStruct.h struct.h number.h
	g++ -std=c++0x -c mainAtom.cpp

atom.o: atom.cpp atom.h variable.h
	g++ -std=c++0x -c atom.cpp

utVariable: mainVariable.o atom.o
		g++ -o utVariable mainVariable.o atom.o -lgtest 
mainVariable.o: mainVariable.cpp utVariable.h variable.h
		g++ -std=c++0x -c mainVariable.cpp


utScanner: mainScanner.o scanner.h utScanner.h
	g++ -o utScanner mainScanner.o -lgtest 
mainScanner.o: mainScanner.cpp utScanner.h scanner.h  atom.h struct.h variable.h
		g++ -std=c++0x -c mainScanner.cpp

clean:
	rm -f *.o madRace utAtom utVariable utScanner hw4
stat:
	wc *.h *.cpp
test:
	make clean
	make
	./hw4
	make clean