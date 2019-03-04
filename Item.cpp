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
Item::Item(std::string name, std::string description, std::string forensicAnalysis, Suspect* suspect, bool usableIn)
{
	setName(name);
	setDescription(description);
	setForensicAnalysis(forensicAnalysis);
	setAvailable(false);
	setAnalyzed(false);
	setBelongsTo(suspect);
	setUseable(usableIn);
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

bool Item::getUseable()
{
	return this->usable;
}

Suspect* Item::getBelongsTo()
{
	return belongsTo;
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

void Item::setUseable(bool newBool)
{
	this->usable = newBool;
}

void Item::setBelongsTo(Suspect* suspect)
{
	belongsTo = suspect;
}



/*******************************************************************************
*		OTHER FUNCTIONS
*******************************************************************************/


void Item::analyzeItem()
{
	this->setAnalyzed(true);
}


void Item::revealedByFeature()
{
	setAvailable(true);
	
	std::cout << "| Your search has revealed " << this->name << "." << std::endl;
	
}

void Item::revealedByHack(std::string nameIn)
{
	setAvailable(true);
	
	std::cout << "| Hacking " << nameIn << " has produced " << this->name << "." << std::endl;
}

void Item::revealedBySample(std::string nameIn)
{
	setAvailable(true);
	
	std::cout << "| taking a sample of " << nameIn << " has added " << this->name << " to your inventory." << std::endl;
}

void Item::revealedByItemUsed(std::string nameIn, std::string usedIn)
{
	setAvailable(true);
	
	std::cout << "| using the " << usedIn << " on the " << nameIn << " has revealed " << this->name << "." << std::endl;
}