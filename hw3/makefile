all: myProgram

myProgram: main.o 
	g++ main.o -o myProgram

main.o: main.cpp
	g++ -c main.cpp

clean:
	rm -rf *o myProgram
