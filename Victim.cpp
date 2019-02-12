/*******************************************************************************
** Program: Capstone Project - Team Homam - W2019
** Author: Rozalija Zibrat (Kendal Droddy, Matthew Garner)
** Date: 17 March 2019
** Description: A murder mystery game where the player has to interrogate
** suspects, investigate the crime scene, search for evidence, and ultimately
** decide who committed the murder.
*******************************************************************************/

#include "Victim.hpp"

/*******************************************************************************
*		CONTRUCTOR
*******************************************************************************/
Victim::Victim(std::string name, std::string description)
{
	setName(name);
	setDescription(description);
}

/*******************************************************************************
*		GET FUNCTIONS
*******************************************************************************/
std::string Victim::getName()
{
	return name;
}

std::string Victim::getDescription()
{
	return description;
}

/*******************************************************************************
*		SET FUNCTIONS
*******************************************************************************/
void Victim::setName(std::string givenName)
{
	name = givenName;
}

void Victim::setDescription(std::string givenDescription)
{
	description = givenDescription;
}
