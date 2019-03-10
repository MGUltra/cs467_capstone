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

}

bool Notebook::getItemAnalyzed(std::string stringIn)
{

}

bool Notebook::getFeatureInspected(std::string stringIn)
{

}

bool Notebook::getFeatureSampled(std::string stringIn)
{

}

bool Notebook::getFeatureActioned(std::string stringIn)
{

}

bool Notebook::getRoomVisited(std::string stringIn)
{

}

std::string Notebook::getItemLocations(std::string stringIn)
{
	
}

std::string Notebook::getCurrentRoom()
{

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

void Notebook::setFeatureSampled(std::string stringIn, bool boolIn)
{
	featureSampled[stringIn] = boolIn;
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
	if(gameFlags["vinceLocketAsk"] == true 		&& 
		 gameFlags["vinceArticleAsk"] == true		&&
		 gameFlags["vinceTicketsAsk"] == true		&&
		 gameFlags["royInterrogated"] == true)
	{
		return true;
	}
	else 
		return false;
}

bool Notebook::vinceCanClear()
{
	if(gameFlags["vinceInterrogated"] == true)
	{
		return true;
	}
	else 
		return false;
}

bool Notebook::carlCanInterrogate()
{

}

bool Notebook::carlCanClear()
{

}

bool Notebook::danCanInterrogate()
{

}

bool Notebook::danCanAccuse()
{

}

bool Notebook::royCanInterrogate()
{
	if(gameFlags["royTapeAsk"] == true &&
		 gameFlags["royCashAsk"] == true)
	{
		return true;
	}
	else 
		return false;
}

bool Notebook::louiseCanInterrogate()
{

}

bool Notebook::herbertCanInterrogate()
{

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