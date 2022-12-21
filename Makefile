CXXFLAGS=-Wall

prog: Chaine.o Programme.o 
	g++ ${CXXFLAGS} $^ -o $@

Programme.o: Chaine.hpp
Programme2.o: Chaine.hpp

clean:
	rm -f *.o prog *.cpp~ *.hpp~ Makefile~ *.txt~ prog2
memcheck:
	valgrind ./prog

prog2: Programme2.o Chaine.o
	g++ $^ -o $@

memcheck2: prog2
	valgrind ./prog2
