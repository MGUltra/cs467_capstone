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
Suspect::Suspect(std::string nameIn,
								std::string inspectResponseIn,
								std::string talkResponseIn,
								std::string interrogateResponseIn,
								std::string accuseResponseTrueIn,
								std::string accuseResponseFalseIn,
								std::string itemResponse1In, 
								std::string itemResponse2In,
								std::string itemResponse3In,
								std::string itemResponseGenericIn,
								bool isGuiltyIn,
								std::string item1,
								std::string item2,
								std::string item3)
{
	setName(nameIn);
	setInspectResponse(inspectResponseIn);
	setTalkResponse(talkResponseIn);
	setInterrogateResponse(interrogateResponseIn);
	setAccuseResponseTrue(accuseResponseTrueIn);
	setAccuseResponseFalse(accuseResponseFalseIn);
	setItemResponse1(itemResponse1In);
	setItemResponse2(itemResponse2In);
	setItemResponse3(itemResponse3In);
	setItemResponseGeneric(itemResponseGenericIn);
	setIsGuilty(isGuiltyIn);
	setIsCleared(false);
	setItem1(item1);
	setItem2(item2);
	setItem3(item3);

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

std::string Suspect::getInterrogateResponse()
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

std::string Suspect::getItem1()
{
	return item1;
}

std::string Suspect::getItem2()
{
	return item2;
}

std::string Suspect::getItem3()
{
	return item3;
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

void Suspect::setInterrogateResponse(std::string stringIn)
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

void Suspect::setItem1(std::string stringIn)
{

	item1 = stringIn;
}

void Suspect::setItem2(std::string stringIn)
{

	item2 = stringIn;
}

void Suspect::setItem3(std::string stringIn)
{

	item3 = stringIn;
}


	
/*******************************************************************************
*		OTHER FUNCTIONS
*******************************************************************************/

std::string Suspect::askItemResponse(std::string itemIn, Notebook* notebook)
{	
	// VINCE
	if(this->getName() == "vince")
	{
		if(itemIn == item1) // tickets
		{
			
			if(notebook->getItemAnalyzed(itemIn) == true)
			{			
				if(notebook->getGameFlags("vinceTicketsAsk") == false)
				{
					notebook->setGameFlags("vinceTicketsAsk", true);
				}
				
				return getItemResponse1();
			}
			else
			{
				std::cout << "You may need to analyze this item to get a better response" << std::endl;
				return getItemResponseGeneric();					
			}
		}
		else if(itemIn == item2) // locket
		{
			if(notebook->getItemAnalyzed(itemIn) == true)
			{		
				if(notebook->getGameFlags("vinceLocketAsk") == false)
				{
					notebook->setGameFlags("vinceLocketAsk", true);
				}
				return getItemResponse2();
			}
			else
			{
				std::cout << "You may need to analyze this item to get a better response" << std::endl;
				return getItemResponseGeneric();	
			}
		}
		else if(itemIn == item3) // cash
		{
			if(notebook->getItemAnalyzed(itemIn) == true)
			{		
				if(notebook->getGameFlags("vinceCashAsk") == false)
				{
					notebook->setGameFlags("vinceCashAsk", true);
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
	// CARL
	else if(this->getName() == "carl")
	{
		if(itemIn == item1) // Flutes
		{
			if(notebook->getItemAnalyzed(itemIn) == true)
			{		
				if(notebook->getGameFlags("carlFlutesAsk") == false)
				{
					notebook->setGameFlags("carlFlutesAsk", true);
				}
				return getItemResponse1();
			}
			else
			{
				std::cout << "You may need to analyze this item to get a better response" << std::endl;
				return getItemResponseGeneric();				
			}			
		}
		else if(itemIn == item2) // letters
		{
			if(notebook->getItemAnalyzed(itemIn) == true)
			{		
				if(notebook->getGameFlags("carlLettersAsk") == false)
				{
					notebook->setGameFlags("carlLettersAsk", true);
				}
				return getItemResponse2();
			}
			else
			{
				std::cout << "You may need to analyze this item to get a better response" << std::endl;
				return getItemResponseGeneric();				
			}			
		}
		else if(itemIn == item3) // spreadsheet
		{
			if(notebook->getItemAnalyzed(itemIn) == true)
			{		
				if(notebook->getGameFlags("carlSpreadsheetAsk") == false)
				{
					notebook->setGameFlags("carlSpreadsheetAsk", true);
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
	// DAN
	else
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
}

