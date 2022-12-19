#CXXFLAGS=-Wall

prog: Programme.cpp Chaine.cpp
	g++ -ggdb $^ -o $@
	./$@

clean:
	rm -f *.o prog *.cpp~
