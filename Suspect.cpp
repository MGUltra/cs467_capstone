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

}

/*******************************************************************************
*		GET FUNCTIONS
*******************************************************************************/
std::string Suspect::getName()
{
	return name;
}

std::string Suspect::getInspectResponse()
{
	return inspectResponse;
}

std::string Suspect::getTalkResponse()
{
	
}

std::string Suspect::getIinterrogateResponse()
{
	
}

std::string Suspect::getAccuseResponseTrue()
{
	
}

std::string Suspect::getAccuseResponseFalse()
{
	
}

std::string Suspect::getItemResponse1()
{
	
}

std::string Suspect::getItemResponse2()
{
	
}

std::string Suspect::getItemResponse3()
{
	
}

std::string Suspect::getInspectResponse()
{
	
}



/*******************************************************************************
*		SET FUNCTIONS
*******************************************************************************/
void Suspect::setName(std::string givenName)
{
	name = givenName;
}

void Suspect::setInspectResponse(std::string giveninspectResponse)
{
	inspectResponse = giveninspectResponse;
}

void Suspect::setTalkResponse(std::string)
{
	
}

void Suspect::setIinterrogateResponse(std::string)
{
	
}

void Suspect::setAccuseResponseTrue(std::string)
{
	
}

void Suspect::setAccuseResponseFalse(std::string)
{
	
}

void Suspect::setItemResponse1(std::string)
{
	
}

void Suspect::setItemResponse2(std::string)
{
	
}

void Suspect::setItemResponse3(std::string)
{
	
}

void Suspect::setInspectResponse(std::string)
{
	
}

