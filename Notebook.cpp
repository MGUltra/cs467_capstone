/*******************************************************************************
** Program: Capstone Project - Team Homam - W2019
** Author: Rozalija Zibrat (Kendal Droddy, Matthew Garner)
** Date: 17 March 2019
** Description: A murder mystery game where the player has to interrogate
** suspects, investigate the crime scene, search for evidence, and ultimately
** decide who committed the murder.
*******************************************************************************/

#include "Notebook.hpp"

/*******************************************************************************
*		CONTRUCTOR
*******************************************************************************/
Notebook::Notebook()
{
	
}


/*******************************************************************************
*		GET FUNCTIONS
*******************************************************************************/


bool Notebook::getGameFlags(std::string stringIn)
{
	return gameFlags[stringIn];
}

bool Notebook::getItemAvailable(std::string stringIn)
{
	return itemAvailable[stringIn];
}

bool Notebook::getItemAnalyzed(std::string stringIn)
{
	return itemAnalyzed[stringIn];
}

bool Notebook::getFeatureInspected(std::string stringIn)
{
	return featureInspected[stringIn];
}

bool Notebook::getFeatureActioned(std::string stringIn)
{
	return featureActioned[stringIn];
}

bool Notebook::getRoomVisited(std::string stringIn)
{
	return roomVisited[stringIn];
}

std::string Notebook::getItemLocations(std::string stringIn)
{
	return itemLocations[stringIn];
}

std::string Notebook::getCurrentRoom()
{
	return playerLocation;
}

	
/*******************************************************************************
*		ADD FUNCTION
*******************************************************************************/
void Notebook::changeEntry(std::string name, bool entry)
{
	gameFlags[name] = entry;
}

void Notebook::setGameFlags(std::string stringIn, bool boolIn)
{
	gameFlags[stringIn] = boolIn;
}

void Notebook::setItemAvailable(std::string stringIn, bool boolIn)
{
	itemAvailable[stringIn] = boolIn;
}

void Notebook::setItemAnalyzed(std::string stringIn, bool boolIn)
{
	itemAnalyzed[stringIn] = boolIn;
}

void Notebook::setFeatureInspected(std::string stringIn, bool boolIn)
{
	featureInspected[stringIn] = boolIn;
}

void Notebook::setFeatureActioned(std::string stringIn, bool boolIn)
{
	featureActioned[stringIn] = boolIn;
}

void Notebook::setRoomVisited(std::string stringIn, bool boolIn)
{
	roomVisited[stringIn] = boolIn;
}

void Notebook::setItemLocations(std::string itemNameIn, std::string roomNameIn)
{
	itemLocations[itemNameIn] = roomNameIn;
}

void Notebook::setCurrentRoom(std::string stringIn)
{
	playerLocation == stringIn;
}

	
/*******************************************************************************
*		PROGRESS CHECK FUNCTIONS
*******************************************************************************/

	
bool Notebook::vinceCanInterrogate()
{
	if(this->gameFlags["vinceLocketAsk"] 	== true		&& 
		 this->gameFlags["vinceCashAsk"] 		== true		&&
		 this->gameFlags["vinceTicketsAsk"] == true		&&
		 this->gameFlags["royInterrogated"] == true		&&
		 this->itemAnalyzed["article"] 			== true)
	{
		return true;
	}
	else 
		return false;
}

bool Notebook::vinceCanClear()
{
	if(this->gameFlags["vinceInterrogated"] == true)
	{
		return true;
	}
	else 
		return false;
}

bool Notebook::carlCanInterrogate()
{
	if(this->gameFlags[""] == true)
	{
		return true;
	}
	else 
		return false;
}

bool Notebook::carlCanClear()
{
	if(this->gameFlags[""] == true)
	{
		return true;
	}
	else 
		return false;
}

bool Notebook::danCanInterrogate()
{
	if(this->gameFlags[""] == true)
	{
		return true;
	}
	else 
		return false;
}

bool Notebook::danCanAccuse()
{
	if(this->gameFlags[""] == true)
	{
		return true;
	}
	else 
		return false;
}

bool Notebook::royCanInterrogate()
{
	if(this->gameFlags["royRecordingAsk"] == true	&&
		 this->gameFlags["royCashAsk"] 			== true)
	{
		return true;
	}
	else 
		return false;
}

bool Notebook::louiseCanInterrogate()
{
	if(this->gameFlags[""] == true)
	{
		return true;
	}
	else 
		return false;
}

bool Notebook::herbertCanInterrogate()
{
	if(this->gameFlags[""] == true)
	{
		return true;
	}
	else 
		return false;
}

	
	
/*******************************************************************************
*		SAVE / LOAD FUNCTIONs
*******************************************************************************/
	
void Notebook::saveGame()
{
	
}



void Notebook::loadGame()
{
	
}


/*******************************************************************************
*		SAVE / LOAD FUNCTIONs
*******************************************************************************/

void Notebook::printGameFlags()
{
	  std::cout << "Gameflags:" << std::endl;
		
  for ( auto it = gameFlags.begin(); it != gameFlags.end(); ++it )
    std::cout << " " << it->first << ":" << it->second << std::endl;
  
	std::cout << std::endl;
}

void Notebook::printAll()
{
	
}
