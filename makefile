all: hw8 shell

hw8: mainExp.o atom.o struct.o list.o parser.h scanner.h exp.h 
ifeq (${OS}, Windows_NT)
	g++ -o hw8 mainExp.o struct.o list.o atom.o -lgtest
else
	g++ -o hw8 mainExp.o struct.o list.o atom.o -lgtest -lpthread
endif

shell: shell.o atom.o struct.o list.o parser.h scanner.h exp.h atom.h variable.h iterator.h
ifeq (${OS}, Windows_NT)
	g++ -o shell shell.o struct.o list.o atom.o -lgtest
else
	g++ -o shell shell.o struct.o list.o atom.o -lgtest -lpthread
endif

shell.o:  shell.cpp atom.h list.h scanner.h parser.h global.h \
		  variable.h struct.h iterator.h \
		  struct.o list.o atom.o
	g++ -std=gnu++0x -c shell.cpp

mainExp.o: mainExp.cpp atom.h list.h scanner.h parser.h global.h \
		   variable.h struct.h iterator.h exception.h expression.h \
		   struct.o list.o atom.o
	g++ -std=gnu++0x -c mainExp.cpp

atom.o: atom.cpp atom.h variable.h
	g++ -std=gnu++0x -c atom.cpp

list.o: list.cpp list.h
		g++ -std=gnu++0x -c list.cpp
struct.o:struct.cpp struct.h
		 g++ -std=gnu++0x -c struct.cpp

# exp: mainExp.o
# 	g++ -o exp mainExp.o -lgtest -lpthread

clean:
	rm -f *.o hw8 shell
stat:
	wc *.h *.cpp
hw:
	make clean
	make hw8
	./hw8
s:
	make clean
	make shell
	./shell