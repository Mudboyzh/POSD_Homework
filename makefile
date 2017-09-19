INC_DIR = include

all: utSort
utSort: main.o Shapes.o Media.o
ifeq (${OS}, Windows_NT)
	g++ -o utSort main.o Shapes.o Media.o -lgtest
else
	g++ -o utSort main.o Shapes.o Media.o -lgtest -lpthread
endif
	
main.o: main.cpp utSort.h
	g++ -std=gnu++0x -c main.cpp
Shapes.o: Shapes.cpp $(INC_DIR)/Shapes.h
	g++ -std=gnu++0x -c Shapes.cpp
Media.o: Media.cpp $(INC_DIR)/Media.h 
	g++ -std=gnu++0x -c Media.cpp

clean:	
ifeq (${OS}, Windows_NT)
	del *.o *.exe
else
	rm -f *.o exp
endif