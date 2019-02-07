all: test

clean:
	-rm parser.o word.o verb.o noun.o wordtest

test: wordtest parsertest
	
wordtest: word.o verb.o noun.o parser.o wordTest.cpp
	g++ -g -std=c++11 -o wordtest wordTest.cpp word.o verb.o noun.o

parsertest: word.o verb.o noun.o parser.o parserTest.cpp
	g++ -g -std=c++11 -o parsertest parserTest.cpp word.o verb.o noun.o parser.o
	
parser.o: parser.hpp parser.cpp
	g++ -c -g -std=c++11 parser.cpp
	
word.o: word.hpp word.cpp
	g++ -c -g -std=c++11 word.cpp

verb.o: verb.hpp verb.cpp
	g++ -c -g -std=c++11 verb.cpp

noun.o: noun.hpp noun.cpp word.hpp
	g++ -c -g -std=c++11 noun.cpp