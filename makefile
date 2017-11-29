all: madRace utAtom utVariable utScanner

madRace: mainMadRace.o
	g++ -o madRace mainMadRace.o -lgtest 
mainMadRace.o: mainMadRace.cpp madRace.h utMadRace.h
	g++ -std=gnu++0x -c mainMadRace.cpp

utAtom: mainAtom.o atom.o
	g++ -o utAtom mainAtom.o atom.o -lgtest 
mainAtom.o: mainAtom.cpp utAtom.h atom.h utStruct.h struct.h
	g++ -std=gnu++0x -c mainAtom.cpp

atom.o: atom.cpp atom.h variable.h
	g++ -std=gnu++0x -c atom.cpp

utVariable: mainVariable.o atom.o
		g++ -o utVariable mainVariable.o atom.o -lgtest 
mainVariable.o: mainVariable.cpp utVariable.h variable.h
		g++ -std=gnu++0x -c mainVariable.cpp
list.o:list.cpp list.h
		g++ -std=gnu++0x -c list.cpp
#exp: mainExp.o
#	g++ -o exp mainExp.o -lgtest 
#mainExp.o: mainExp.cpp exp.h global.h
#	g++ -std=gnu++0x -c mainExp.cpp

utScanner: mainScanner.o atom.o list.o scanner.h utScanner.h utParser.h parser.h
	g++ -o hw6 mainScanner.o atom.o list.o -lgtest 
mainScanner.o: mainScanner.cpp utScanner.h scanner.h  atom.h struct.h variable.h  utParser.h parser.h
		g++ -std=gnu++0x -c mainScanner.cpp
utIterator: mainIterator.o atom.o list.o iterator.h
	g++ -o utIterator mainIterator.o atom.o list.o struct.h -lgtest 

mainIterator.o: mainIterator.cpp utIterator.h
	g++ -std=gnu++0x -c mainIterator.cpp


#utTerm: mainTerm.o term.o struct.o var.o list.o
#	g++ -o utTerm mainTerm.o term.o var.o struct.o list.o -lgtest 
#mainTerm.o: mainTerm.cpp utTerm.h term.h var.h utStruct.h struct.h list.h utList.h
#	g++ -std=gnu++0x -c mainTerm.cpp
#term.o: term.h term.cpp
#	g++ -std=gnu++0x -c term.cpp
#struct.o: struct.h struct.cpp
#	g++ -std=gnu++0x -c struct.cpp
#var.o: var.h var.cpp
#g++ -std=gnu++0x -c var.cpp
#list.o: list.h list.cpp term.h var.h
#	g++ -std=gnu++0x -c list.cpp
clean:
	rm -f *.o madRace utAtom utVariable utScanner
stat:
	wc *.h *.cpp

test:
	make utScanner
	./hw6