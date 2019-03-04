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
Witness::Witness(std::string nameIn,
								std::string inspectIn, 
								std::string talkIn, 
								std::string interrogateIn, 
								std::string accuseIn,
								std::string item1In, 
								std::string item2In, 
								std::string item3In, 
								std::string itemGeneric, 
								Room* location)
{
	setName(nameIn);
	setInspectResponse(inspectIn);
	setTalkResponse(talkIn);
	setInterrogateResponse(interrogateIn);
	setAccuseResponse(accuseIn);
	setItemResponse1(item1In);
	setItemResponse2(item2In);
	setItemResponse3(item3In);
	setItemResponseGeneric(itemGeneric);
	setLocation(location);
}

/*******************************************************************************
*		GET FUNCTIONS
*******************************************************************************/
std::string Witness::getName()
{
	return name;
}

std::string Witness::getInspectResponse()
{
	return inspectResponse;
}

std::string Witness::getTalkResponse()
{
	return talkResponse;
}

std::string Witness::getInterrogateResponse()
{
	return interrogateResponse;
}

std::string Witness::getAccuseResponse()
{
	return accuseResponse;
}

std::string Witness::getItemResponse1()
{
	return itemResponse1;
}

std::string Witness::getItemResponse2()
{
	return itemResponse2;
}

std::string Witness::getItemResponse3()
{
	return itemResponse3;
}

std::string Witness::getItemResponseGeneric()
{
	return itemResponseGeneric;
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

void Witness::setInspectResponse(std::string stringin)
{
	this->inspectResponse = stringin;
}


void Witness::setTalkResponse(std::string stringin)
{
	this->talkResponse = stringin;
}


void Witness::setInterrogateResponse(std::string stringin)
{
	this->interrogateResponse = stringin;
}


void Witness::setAccuseResponse(std::string stringin)
{
	this->accuseResponse = stringin;
}


void Witness::setItemResponse1(std::string stringin)
{
	this->itemResponse1 = stringin;
}


void Witness::setItemResponse2(std::string stringin)
{
	this->itemResponse2 = stringin;
}


void Witness::setItemResponse3(std::string stringin)
{
	this->itemResponse3 = stringin;
}


void Witness::setItemResponseGeneric(std::string stringin)
{
	this->itemResponseGeneric= stringin;
}



void Witness::setLocation(Room* givenLocation)
{
	location = givenLocation;
}