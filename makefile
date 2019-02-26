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
DRIVEROBJECTS = Room.o Player.o Victim.o Suspect.o Feature.o Inventory.o Item.o GameDriver.o Witness.o Notebook.o
DRIVERSRCS = Room.cpp Player.cpp Victim.cpp Suspect.cpp Feature.cpp Inventory.cpp Item.cpp GameDriver.cpp Witness.cpp Notebook.cpp
DRIVERHEADERS = Room.hpp Player.hpp Victim.hpp Suspect.hpp Feature.hpp Inventory.hpp Item.hpp Witness.hpp Notebook.hpp dataRead.hpp

# Data Read test Variables
ROOMTESTSRCS = dataTest.cpp
ROOMTESTHEADERS = dataRead.hpp

#include "Room.hpp"
#include "Player.hpp"
#include "Victim.hpp"
#include "Suspect.hpp"
#include "parser.hpp"


all: gamedriver test

clean:
	-rm ${PARSEOBJECTS} ${DRIVEROBJECTS} parsertest gamedriver wordtest roomtest
#-rm parser.o word.o verb.o noun.o wordtest.o parsertest.o wordtest parsertest

test: roomtest

wordtest: word.o verb.o noun.o parser.o wordTest.cpp
	g++ -g -std=c++11 -o wordtest wordTest.cpp word.o verb.o noun.o
	
#parsertest: word.o verb.o noun.o parser.o parserTest.cpp
#	g++ -g -std=c++11 -o parsertest parserTest.cpp word.o verb.o noun.o parser.o

roomtest: ${ROOMTESTHEADERS} 
	${CXX} -std=c++11 ${ROOMTESTSRCS} -o roomtest
	
parsertest: ${PARSEOBJECTS} ${PARSEHEADERS}
	${CXX} -std=c++11 ${PARSEOBJECTS} parserTest.cpp -o parsertest
	
gamedriver: ${DRIVEROBJECTS} ${DRIVERHEADERS} ${PARSEHEADERS}
	${CXX} ${DRIVEROBJECTS} ${PARSEOBJECTS} -o gamedriver
	
	
	
	
# Create Objects

${PARSEOBJECTS}: ${PARSESRCS}
	${CXX} ${CXXFLAGS} -c $(@:.o=.cpp)
	
${DRIVEROBJECTS}: ${DRIVERSRCS} ${PARSEOBJECTS}
	${CXX} ${CXXFLAGS} -c $(@:.o=.cpp)





	
	