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
Suspect::Suspect(std::string name, std::string description, std::string answer1, std::string answer2)
{
	setName(name);
	setDescription(description);
	setAnswer1(answer1);
	setAnswer2(answer2);

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

std::string Suspect::getAnswer1()
{
	return answer1;
}

std::string Suspect::getAnswer2()
{
	return answer2;
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

void Suspect::setAnswer1(std::string givenAnswer1)
{
	answer1 = givenAnswer1;
}

void Suspect::setAnswer2(std::string givenAnswer2)
{
	answer2 = givenAnswer2;
}

void Suspect::setSigItemFound()
{
	sigItemFound = true;
}