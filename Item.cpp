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
Item::Item(std::string name, std::string description, std::string forensicAnalysis)
{
	setName(name);
	setDescription(description);
	setForensicAnalysis(forensicAnalysis);

}

/*******************************************************************************
*		GET FUNCTIONS
*******************************************************************************/
std::string Item::getName()
{
	return name;
}

std::string Item::getDescription()
{
	return description;
}

std::string Item::getForensicAnalysis()
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
void Item::setName(std::string givenName)
{
	name = givenName;
}

void Item::setDescription(std::string givenDescription)
{
	description = givenDescription;
}

void Item::setForensicAnalysis(std::string givenForensicAnalysis)
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
