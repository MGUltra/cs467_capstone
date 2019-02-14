/*******************************************************************************
** Program: Capstone Project - Team Homam - W2019
** Author: Rozalija Zibrat (Kendal Droddy, Matthew Garner)
** Date: 17 March 2019
** Description: A murder mystery game where the player has to interrogate
** suspects, investigate the crime scene, search for evidence, and ultimately
** decide who committed the murder.
*******************************************************************************/

#include "Feature.hpp"

/*******************************************************************************
*		CONTRUCTOR
*******************************************************************************/
Feature::Feature(std::string name, std::string description, std::string location, Item* itemAffected)
{
	setName(name);
	setDescription(description);
	setLocation(location);
	setItemAffected(itemAffected);
	alreadyInspected = false;
}

/*******************************************************************************
*		GET FUNCTIONS
*******************************************************************************/
std::string Feature::getName()
{
	return name;
}

std::string Feature::getDescription()
{
	return description;
}

std::string Feature::getLocation()
{
	return location;
}

/*******************************************************************************
*		SET FUNCTIONS
*******************************************************************************/
void Feature::setName(std::string givenName)
{
	name = givenName;
}

void Feature::setDescription(std::string givenDescription)
{
	description = givenDescription;
}

void Feature::setLocation(std::string givenLocation)
{
	location = givenLocation;
}

void Feature::setAlreadyInspected(bool newBool)
{
	alreadyInspected = newBool;
}

void Feature::setItemAffected(Item* newItem)
{
	this->itemAffected = newItem;
}


void Feature::inspected()
{
	this->itemAffected->setAvailable(true);
	
	std::cout << "You take a closer look at the " << this->getName() << "." << std::endl;
}