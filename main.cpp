/*------------------------------------------------------------------------------
		LIBRARIES
------------------------------------------------------------------------------*/
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_map>

#include "Gamedriver.hpp"


int main()
{
        std::ifstream inFile;

        int winFlag = calcWindowSize();
        if (winFlag == 0)
          return 0;	
        
        inFile.open("gameText/titleScreen.txt");
        readFileDefault(inFile);
        inFile.close();

	Gamestate* newGame;
	
	newGame = new Gamestate();
	
	newGame->createGame();
	
	newGame->playGame();
	
	newGame->cleanup();
	
	delete newGame;
	
	return 0;
}
