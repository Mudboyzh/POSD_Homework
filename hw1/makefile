INC_DIR = include

all: main	
main: main.o Shapes.o Media.o
ifeq (${OS}, Windows_NT)
	g++ -o hw1 main.o Shapes.o Media.o -lgtest
else
	g++ -o hw1 main.o Shapes.o Media.o -lgtest -lpthread
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
	rm -f *.o hw1
endif