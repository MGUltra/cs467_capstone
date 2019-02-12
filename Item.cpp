/*******************************************************************************
** Program: Capstone Project - Team Homam - W2019
** Author: Rozalija Zibrat (Kendal Droddy, Matthew Garner)
** Date: 17 March 2019
** Description: A murder mystery game where the player has to interrogate
** suspects, investigate the crime scene, search for evidence, and ultimately
** decide who committed the murder.
*******************************************************************************/

#include "Item.hpp"

/*******************************************************************************
*		CONTRUCTOR
*******************************************************************************/
Item::Item(string name, string description, string forensicAnalysis)
{
	setName(name);
	setDescription(description);
	setForensicAnalysis(forensicAnalysis);

}

/*******************************************************************************
*		GET FUNCTIONS
*******************************************************************************/
string Item::getName()
{
	return name;
}

string Item::getDescription()
{
	return description;
}

string Item::getForensicAnalysis()
{
	return forensicAnalysis;
}

bool Item::getAvailable()
{
	return this->available;
}
bool Item::getAnalyzed()
{
	return this->analyzed;
}


/*******************************************************************************
*		SET FUNCTIONS
*******************************************************************************/
void Item::setName(string givenName)
{
	name = givenName;
}

void Item::setDescription(string givenDescription)
{
	description = givenDescription;
}

void Item::setForensicAnalysis(string givenForensicAnalysis)
{
	forensicAnalysis = givenForensicAnalysis;
}

void Item::setAvailable(bool newBool)
{
	this->available = newBool;
}

void Item::setAnalyzed(bool newBool)
{
	this->analyzed = newBool;
}
