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

}

void Notebook::setItemAnalyzed(std::string stringIn, bool boolIn)
{

}

void Notebook::setFeatureInspected(std::string stringIn, bool boolIn)
{

}

void Notebook::setFeatureSampled(std::string stringIn, bool boolIn)
{

}

void Notebook::setFeatureActioned(std::string stringIn, bool boolIn)
{

}

void Notebook::setRoomVisited(std::string stringIn, bool boolIn)
{

}

void Notebook::setCurrentRoom(std::string stringIn)
{

}

	
/*******************************************************************************
*		PROGRESS CHECK FUNCTIONS
*******************************************************************************/

bool Notebook::vinceInterrogate()
{

}

bool Notebook::vinceClear()
{

}

bool Notebook::carlInterrogate()
{

}

bool Notebook::carlClear()
{

}

bool Notebook::danInterrogate()
{

}

bool Notebook::danAccuse()
{

}


bool Notebook::royInterrogate()
{

}

bool Notebook::louiseInterrogate()
{

}

bool Notebook::herbertInterrogate()
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