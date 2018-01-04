all: hw8

hw8: mainExp.o

ifeq (${OS}, Windows_NT)
	g++ -o hw8 mainExp.o struct.o list.o atom.o -lgtest
else
	g++ -o hw8 mainExp.o struct.o list.o atom.o -lgtest -lpthread
endif

mainExp.o: mainExp.cpp atom.h list.h scanner.h parser.h global.h \
		   variable.h struct.h iterator.h exception.h expression.h \
		   struct.o list.o atom.o
	g++ -std=gnu++0x -c mainExp.cpp

atom.o: atom.cpp atom.h variable.h
	g++ -std=gnu++0x -c atom.cpp

list.o:list.cpp list.h
		g++ -std=gnu++0x -c list.cpp
struct.o:struct.cpp struct.h iterator.h
		g++ -std=gnu++0x -c struct.cpp

# exp: mainExp.o
# 	g++ -o exp mainExp.o -lgtest -lpthread

clean:
	rm -f *.o hw8
stat:
	wc *.h *.cpp
test:
	make clean
	make
	./hw8