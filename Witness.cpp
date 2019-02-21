/*******************************************************************************
** Program: Capstone Project - Team Homam - W2019
** Author: Rozalija Zibrat (Kendal Droddy, Matthew Garner)
** Date: 17 March 2019
** Description: A murder mystery game where the player has to interrogate
** suspects, investigate the crime scene, search for evidence, and ultimately
** decide who committed the murder.
*******************************************************************************/

#include "Witness.hpp"

/*******************************************************************************
*		CONTRUCTOR
*******************************************************************************/
Witness::Witness(std::string name, std::string introduction, std::string answer1, std::string answer2, Room* location)
{
	setName(name);
	setIntroduction(introduction);
	setAnswer1(answer1);
	setAnswer2(answer2);
	setLocation(location);
}

/*******************************************************************************
*		GET FUNCTIONS
*******************************************************************************/
std::string Witness::getName()
{
	return name;
}

std::string Witness::getIntroduction()
{
	return introduction;
}

std::string Witness::getAnswer1()
{
	return answer1;
}

std::string Witness::getAnswer2()
{
	return answer2;
}

Room* Witness::getLocation()
{
	return location;
}

/*******************************************************************************
*		SET FUNCTIONS
*******************************************************************************/
void Witness::setName(std::string givenName)
{
	name = givenName;
}

void Witness::setIntroduction(std::string givenIntroduction)
{
	introduction = givenIntroduction;
}

void Witness::setAnswer1(std::string givenAnswer1)
{
	answer1 = givenAnswer1;
}

void Witness::setAnswer2(std::string givenAnswer2)
{
	answer2 = givenAnswer2;
}

void Witness::setLocation(Room* givenLocation)
{
	location = givenLocation;
}