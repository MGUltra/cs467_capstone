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
	
	Gamestate* newGame;
	
	newGame = new Gamestate();
	
	newGame->createGame();
	
	newGame->playGame();
	
	newGame->cleanup();
	
	delete newGame;
	
	return 0;
}