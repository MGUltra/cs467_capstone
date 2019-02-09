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
Victim::Victim(string name, string description)
{
	setName(name);
	setDescription(description);
}

/*******************************************************************************
*		GET FUNCTIONS
*******************************************************************************/
string Victim::getName()
{
	return name;
}

string Victim::getDescription()
{
	return description;
}

/*******************************************************************************
*		SET FUNCTIONS
*******************************************************************************/
void Victim::setName(string givenName)
{
	name = givenName;
}

void Victim::setDescription(string givenDescription)
{
	description = givenDescription;
}
