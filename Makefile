CC=g++
CFLAGS=-std=c++11 -pedantic -Wall -Wextra -g

digraphAnalyzer: digraphAnalyzer.o digraph.o 
	$(CC) -o digraphAnalyzer digraphAnalyzer.o digraph.o 

digraphAnalyzer.o: digraphAnalyzer.cpp digraph.cpp digraph.h 
	$(CC) $(CFLAGS) -c digraphAnalyzer.cpp digraph.cpp 

digraph.o: digraph.cpp digraph.h
	$(CC) $(CFLAGS) -c digraph.cpp

clean:
	rm -f *.o digraphAnalyzer

