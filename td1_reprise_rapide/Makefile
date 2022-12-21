all: *.cpp
	g++ -g $^ -o $@
	./$@

memcheck: all
	valgrind ./$^


clean:
	rm -f Makefile~ *.hpp~ *.cpp~ a.out all
