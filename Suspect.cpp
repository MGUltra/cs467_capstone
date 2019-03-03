/*******************************************************************************
** Program: Capstone Project - Team Homam - W2019
** Author: Rozalija Zibrat (Kendal Droddy, Matthew Garner)
** Date: 17 March 2019
** Description: A murder mystery game where the player has to interrogate
** suspects, investigate the crime scene, search for evidence, and ultimately
** decide who committed the murder.
*******************************************************************************/

#include "Suspect.hpp"

/*******************************************************************************
*		CONTRUCTOR
*******************************************************************************/
Suspect::Suspect(std::string name, std::string description)
{
	setName(name);
	setDescription(description);


	sigItemFound = false;
}

/*******************************************************************************
*		GET FUNCTIONS
*******************************************************************************/
std::string Suspect::getName()
{
	return name;
}

std::string Suspect::getDescription()
{
	return description;
}



bool Suspect::getSigItemFound()
{
	return sigItemFound;
}

/*******************************************************************************
*		SET FUNCTIONS
*******************************************************************************/
void Suspect::setName(std::string givenName)
{
	name = givenName;
}

void Suspect::setDescription(std::string givenDescription)
{
	description = givenDescription;
}


void Suspect::setSigItemFound()
{
	sigItemFound = true;
}