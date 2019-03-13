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
								Room* location,
								std::string item1, 
								std::string item2, 
								std::string item3)
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
	setItem1(item1);
	setItem2(item2);
	setItem3(item3);
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

std::string Witness::getItem1()
{
	return item1;
}

std::string Witness::getItem2()
{
	return item2;
}

std::string Witness::getItem3()
{
	return item3;
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

void Witness::setItem1(std::string stringin)
{
	this->item1 = stringin;
}

void Witness::setItem2(std::string stringin)
{
	this->item2 = stringin;
}

void Witness::setItem3(std::string stringin)
{
	this->item3 = stringin;
}

void Witness::setLocation(Room* givenLocation)
{
	location = givenLocation;
}



/*******************************************************************************
*		OTHER FUNCTIONS
*******************************************************************************/
std::string Witness::askItemResponse(std::string itemIn, Notebook* notebook)
{
	// ROY
	if(this->getName() == "roy") 
	{
		if(itemIn == item1) // recording
		{
			
			if(notebook->getItemAnalyzed(itemIn) == true)
			{
				if(notebook->getGameFlags("royRecordingAsk") == false)
				{
					notebook->setGameFlags("royRecordingAsk", true);
				}
				
				return getItemResponse1();
			}
			else
			{
				std::cout << "You may need to analyze this item to get a better response" << std::endl;
				
				return getItemResponseGeneric();	
			}
		}
		else if(itemIn == item2) // tickets
		{
			return getItemResponse2();
		}
		else if(itemIn == item3) // cash
		{
			if(notebook->getItemAnalyzed(itemIn) == true)
			{
				if(notebook->getGameFlags("royCashAsk") == false)
				{
					notebook->setGameFlags("royCashAsk", true);
				}
				return getItemResponse3();
			}
			else
			{
				std::cout << "You may need to analyze this item to get a better response" << std::endl;
				
				return getItemResponseGeneric();				
			}
		}
		else
			return getItemResponseGeneric();
	}
	// HERBERT
	else if(this->getName() == "herbert")
	{
		if(itemIn == item1)
		{
			
			return getItemResponse1();
		}
		else if(itemIn == item2)
		{
			
			return getItemResponse2();
		}
		else if(itemIn == item3)
		{
			
			return getItemResponse3();
		}
		else
			return getItemResponseGeneric();		
	}
	// LOUISE
	else
	{
		if(itemIn == item1)
		{
			if(notebook->getItemAnalyzed(itemIn) == true)
			{
				if(notebook->getGameFlags("louiseFlutesAsk") == false)
				{
					notebook->setGameFlags("louiseFlutesAsk", true);
				}
				
				return getItemResponse1();
			}
			else
			{
				std::cout << "You may need to analyze this item to get a better response" << std::endl;
				
				return getItemResponseGeneric();	
			}
		
		}
		else if(itemIn == item2)
		{
			if(notebook->getItemAnalyzed(itemIn) == true)
			{
				if(notebook->getGameFlags("louiseLettersAsk") == false)
				{
					notebook->setGameFlags("louiseLettersAsk", true);
				}
				
				return getItemResponse2();
			}
			else
			{
				std::cout << "You may need to analyze this item to get a better response" << std::endl;
				
				return getItemResponseGeneric();	
			}
					
		}
		else if(itemIn == item3)
		{
			if(notebook->getItemAnalyzed(itemIn) == true)
			{
				if(notebook->getGameFlags("louiseSpreadsheetAsk") == false)
				{
					notebook->setGameFlags("louiseSpreadsheetAsk", true);
				}
				
				return getItemResponse3();
			}
			else
			{
				std::cout << "You may need to analyze this item to get a better response" << std::endl;
				
				return getItemResponseGeneric();	
			}
		}
		else
			return getItemResponseGeneric();		
	}
}

