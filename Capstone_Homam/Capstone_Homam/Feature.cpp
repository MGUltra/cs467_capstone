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
Feature::Feature(string name, string description, Room location)
{
	setName(name);
	setDescription(description);
	setLocation(location);

	alreadyInspected = false;
}

/*******************************************************************************
*		GET FUNCTIONS
*******************************************************************************/
string Feature::getName()
{
	return name;
}

string Feature::getDescription()
{
	return description;
}

Room Feature::getLocation()
{
	return location;
}

/*******************************************************************************
*		SET FUNCTIONS
*******************************************************************************/
void Feature::setName(string givenName)
{
	name = givenName;
}

void Feature::setDescription(string givenDescription)
{
	description = givenDescription;
}

void Feature::setLocation(Room givenLocation)
{
	location = givenLocation;
}