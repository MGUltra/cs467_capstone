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
Suspect::Suspect(string name, string description, string answer1, string answer2)
{
	setName(name);
	setDescription(description);
	setAnswer1(answer1);
	setAnswer2(answer2);
}

/*******************************************************************************
*		GET FUNCTIONS
*******************************************************************************/
string Suspect::getName()
{
	return name;
}

string Suspect::getDescription()
{
	return description;
}

string Suspect::getAnswer1()
{
	return answer1;
}

string Suspect::getAnswer2()
{
	return answer2;
}

/*******************************************************************************
*		SET FUNCTIONS
*******************************************************************************/
void Suspect::setName(string givenName)
{
	name = givenName;
}

void Suspect::setDescription(string givenDescription)
{
	description = givenDescription;
}

void Suspect::setAnswer1(string givenAnswer1)
{
	answer1 = givenAnswer1;
}

void Suspect::setAnswer2(string givenAnswer2)
{
	answer2 = givenAnswer2;
}