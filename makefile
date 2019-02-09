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

# All Variables
#OBJECTS = ${DRIVEROBJECTS} ${PARSEOBJECTS}
#SRCS =
#HEADERS =

# Parser Variables
PARSEOBJECTS = parser.o word.o verb.o noun.o
PARSESRCS = parser.cpp word.cpp verb.cpp noun.cpp
PARSEHEADERS = parser.hpp word.hpp verb.hpp noun.hpp

# Driver Variables
DRIVEROBJECTS = Room.o Player.o Victim.o Suspect.o Feature.o Inventory.o Item.o GameDriver.o
DRIVERSRCS = Room.cpp Player.cpp Victim.cpp Suspect.cpp Feature.cpp Inventory.cpp Item.cpp GameDriver.cpp
DRIVERHEADERS = Room.hpp Player.hpp Victim.hpp Suspect.hpp Feature.hpp Inventory.hpp Item.hpp


#include "Room.hpp"
#include "Player.hpp"
#include "Victim.hpp"
#include "Suspect.hpp"
#include "parser.hpp"


all: test

clean:
	-rm ${PARSEOBJECTS} ${DRIVEROBJECTS} parsertest gamedriver wordtest
#-rm parser.o word.o verb.o noun.o wordtest.o parsertest.o wordtest parsertest

test: wordtest parsertest

wordtest: word.o verb.o noun.o parser.o wordTest.cpp
	g++ -g -std=c++11 -o wordtest wordTest.cpp word.o verb.o noun.o
	
#parsertest: word.o verb.o noun.o parser.o parserTest.cpp
#	g++ -g -std=c++11 -o parsertest parserTest.cpp word.o verb.o noun.o parser.o


parsertest: ${PARSEOBJECTS} ${PARSEHEADERS}
	${CXX} ${PARSEOBJECTS} parserTest.cpp -o parsertest
	
gamedriver: ${DRIVEROBJECTS} ${DRIVERHEADERS} ${PARSEHEADERS}
	${CXX} ${DRIVEROBJECTS} ${PARSEOBJECTS} -o gamedriver
	
	
	
	
# Create Objects

${PARSEOBJECTS}: ${PARSESRCS}
	${CXX} ${CXXFLAGS} -c $(@:.o=.cpp)
	
${DRIVEROBJECTS}: ${DRIVERSRCS} ${PARSEOBJECTS}
	${CXX} ${CXXFLAGS} -c $(@:.o=.cpp)





	
	