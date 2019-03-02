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
bool Notebook::getEntry(std::string name)
{
	return gameFlags[name];
}


/*******************************************************************************
*		ADD FUNCTION
*******************************************************************************/
void Notebook::setEntry(std::string name, bool entry)
{
	gameFlags[name] = entry;
}

void Notebook::changeEntry(std::string name, bool entry)
{
	gameFlags[name] = entry;
}


void Notebook::saveGame()
{
	
}



void Notebook::loadGame()
{
	
}