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
Suspect::Suspect(std::string nameIn, std::string inspectResponseIn, std::string talkResponseIn, std::string interrogateResponseIn,
								 std::string accuseResponseTrueIn, std::string accuseResponseFalseIn, std::string itemResponse1In, 
								 std::string itemResponse2In, std::string itemResponse3In, std::string itemResponseGenericIn, bool isGuiltyIn)
{
	setName(nameIn);
	setInspectResponse(inspectResponseIn);
	setTalkResponse(talkResponseIn);
	setIinterrogateResponse(interrogateResponseIn);
	setAccuseResponseTrue(accuseResponseTrueIn);
	setAccuseResponseFalse(accuseResponseFalseIn);
	setItemResponse1(itemResponse1In);
	setItemResponse2(itemResponse2In);
	setItemResponse3(itemResponse3In);
	setInspectResponse(itemResponseGenericIn);
	setIsGuilty(isGuiltyIn);
	setIsCleared(false);

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
	return talkResponse;
}

std::string Suspect::getIinterrogateResponse()
{
	return interrogateResponse;
}

std::string Suspect::getAccuseResponseTrue()
{
	return accuseResponseTrue;
}

std::string Suspect::getAccuseResponseFalse()
{
	return accuseResponseFalse;
}

std::string Suspect::getItemResponse1()
{
	return itemResponse1;
}

std::string Suspect::getItemResponse2()
{
	return itemResponse2;
}

std::string Suspect::getItemResponse3()
{
	return itemResponse3;
}

std::string Suspect::getItemResponseGeneric()
{
	return itemResponseGeneric;
}

bool Suspect::getIsGuilty()
{
	return isGuilty;
}

bool Suspect::getIsCleared()
{
	return isCleared;
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

void Suspect::setTalkResponse(std::string stringIn)
{
	talkResponse = stringIn;
}

void Suspect::setIinterrogateResponse(std::string stringIn)
{
	interrogateResponse = stringIn;
}

void Suspect::setAccuseResponseTrue(std::string stringIn)
{
	accuseResponseTrue = stringIn;
}

void Suspect::setAccuseResponseFalse(std::string stringIn)
{
	accuseResponseFalse = stringIn;
}

void Suspect::setItemResponse1(std::string stringIn)
{
	itemResponse1 = stringIn;
}

void Suspect::setItemResponse2(std::string stringIn)
{
	itemResponse2 = stringIn;
}

void Suspect::setItemResponse3(std::string stringIn)
{
	itemResponse3 = stringIn;
}

void Suspect::setItemResponseGeneric(std::string stringIn)
{
	itemResponseGeneric = stringIn;
}

void Suspect::setIsGuilty(bool boolIn)
{
	isGuilty = boolIn;
}

void Suspect::setIsCleared(bool boolIn)
{
	isCleared = boolIn;	
}
	
	
