#TESTDIR: ~\test

# Compiler/Flag Variables
CXX=g++
CXXFLAGS = -std=c++11
CXXFLAGS += -g
CXXFLAGS += -Wall
CXXFLAGS += -pedantic
CXXFLAGS += -Wextra
CXXFLAGS += -Weffc++
#LDFLAGS=

# Parser Variables
PARSEOBJECTS = parser.o word.o verb.o noun.o parserTest.o
PARSESRCS = parser.cpp word.cpp verb.cpp noun.cpp
PARSEHEADERS = parser.hpp word.hpp verb.hpp noun.hpp

all: test

clean:
	-rm parser.o word.o verb.o noun.o wordtest.o parsertest.o wordtest parsertest

test: wordtest parsertest


wordtest: word.o verb.o noun.o parser.o wordTest.cpp
	g++ -g -std=c++11 -o wordtest wordTest.cpp word.o verb.o noun.o

#parsertest: word.o verb.o noun.o parser.o parserTest.cpp
#	g++ -g -std=c++11 -o parsertest parserTest.cpp word.o verb.o noun.o parser.o

parsertest: ${PARSEOBJECTS} ${PARSEHEADERS}
	${CXX} ${PARSEOBJECTS} -o parsertest
	
#Objects
	
#parser.o: parser.hpp parser.cpp
#	g++ -c -g -std=c++11 parser.cpp
	
#word.o: word.hpp word.cpp
#	g++ -c -g -std=c++11 word.cpp

#verb.o: verb.hpp verb.cpp
#	g++ -c -g -std=c++11 verb.cpp

#noun.o: noun.hpp noun.cpp
#	g++ -c -g -std=c++11 noun.cpp
#	${CXX} ${CXXFLAGS} -c noun.cpp


${PARSEOBJECTS}: ${PARSESRCS}
	${CXX} ${CXXFLAGS} -c $(@:.o=.cpp)
	
	