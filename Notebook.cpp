/*******************************************************************************
** Program: Capstone Project - Team Homam - W2019
** Author: Rozalija Zibrat (Kendal Droddy, Matthew Garner)
** Date: 17 March 2019
** Description: A murder mystery game where the player has to interrogate
** suspects, investigate the crime scene, search for evidence, and ultimately
** decide who committed the murder.
*******************************************************************************/

#include "Notebook.hpp"

/*******************************************************************************
*		CONTRUCTOR
*******************************************************************************/
Notebook::Notebook()
{
	
}


/*******************************************************************************
*		GET FUNCTIONS
*******************************************************************************/


bool Notebook::getGameFlags(std::string stringIn)
{
	return gameFlags[stringIn];
}

bool Notebook::getItemAvailable(std::string stringIn)
{
	return itemAvailable[stringIn];
}

bool Notebook::getItemAnalyzed(std::string stringIn)
{
	return itemAnalyzed[stringIn];
}

bool Notebook::getFeatureInspected(std::string stringIn)
{
	return featureInspected[stringIn];
}

bool Notebook::getFeatureActioned(std::string stringIn)
{
	return featureActioned[stringIn];
}

bool Notebook::getRoomVisited(std::string stringIn)
{
	return roomVisited[stringIn];
}

std::string Notebook::getItemLocations(std::string stringIn)
{
	return itemLocations[stringIn];
}

std::string Notebook::getCurrentRoom()
{
	return playerLocation;
}

std::unordered_map<std::string, bool>* Notebook::getGameFlags()
{
	return &gameFlags;
}

std::unordered_map<std::string, bool>* Notebook::getItemAvailable()
{
	return &itemAvailable;
}

std::unordered_map<std::string, bool>* Notebook::getItemAnalyzed()
{
	return &itemAnalyzed;
}

std::unordered_map<std::string, bool>* Notebook::getFeatureInspected()
{
	return &featureInspected;
}

std::unordered_map<std::string, bool>* Notebook::getFeatureActioned()
{
	return &featureActioned;
}

std::unordered_map<std::string, bool>* Notebook::getRoomVisited()
{
	return &roomVisited;
}

std::unordered_map<std::string, std::string>* Notebook::getItemLocations()
{
	return &itemLocations;
}

	
/*******************************************************************************
*		ADD FUNCTION
*******************************************************************************/
void Notebook::changeEntry(std::string name, bool entry)
{
	gameFlags[name] = entry;
}

void Notebook::setGameFlags(std::string stringIn, bool boolIn)
{
	gameFlags[stringIn] = boolIn;
}

void Notebook::setItemAvailable(std::string stringIn, bool boolIn)
{
	itemAvailable[stringIn] = boolIn;
}

void Notebook::setItemAnalyzed(std::string stringIn, bool boolIn)
{
	itemAnalyzed[stringIn] = boolIn;
}

void Notebook::setFeatureInspected(std::string stringIn, bool boolIn)
{
	featureInspected[stringIn] = boolIn;
}

void Notebook::setFeatureActioned(std::string stringIn, bool boolIn)
{
	featureActioned[stringIn] = boolIn;
}

void Notebook::setRoomVisited(std::string stringIn, bool boolIn)
{
	roomVisited[stringIn] = boolIn;
}

void Notebook::setItemLocations(std::string itemNameIn, std::string roomNameIn)
{
	itemLocations[itemNameIn] = roomNameIn;
}

void Notebook::setCurrentRoom(std::string stringIn)
{
	playerLocation = stringIn;
}

	
/*******************************************************************************
*		PROGRESS CHECK FUNCTIONS
*******************************************************************************/

	
bool Notebook::vinceCanInterrogate()
{
	if(this->gameFlags["vinceLocketAsk"] 	== true		&& 
		 this->gameFlags["vinceCashAsk"] 		== true		&&
		 this->gameFlags["vinceTicketsAsk"] == true		&&
		 this->gameFlags["royInterrogated"] == true		&&
		 this->itemAnalyzed["article"] 			== true)
	{
		return true;
	}
	else 
		return false;
}

bool Notebook::vinceCanClear()
{
	if(this->gameFlags["vinceInterrogated"] == true)
	{
		return true;
	}
	else 
		return false;
}

bool Notebook::carlCanInterrogate()
{
	if(this->gameFlags["carlLettersAsk"] 			== true	&&
		 this->gameFlags["carlSpreadsheetAsk"] 	== true	&&
		 this->gameFlags["carlFlutesAsk"] 			== true	&&
		 this->gameFlags["louiseInterrogated"] 	== true	&&
		 this->itemAnalyzed["dna"] 							== true	&&
		 this->itemAnalyzed["shirt"] 						== true)
	{
		return true;
	}
	else 
		return false;
}

bool Notebook::carlCanClear()
{
	if(this->gameFlags["carlInterrogated"] == true)
	{
		return true;
	}
	else 
		return false;
}


bool Notebook::danCanInterrogate()
{
	if(this->gameFlags["danTextAsk"]					== true	&&
		 this->gameFlags["danWrenchAsk"]				== true	&&
		 this->gameFlags["danAmmoniaAsk"]				== true	&&
		 this->gameFlags["herbertInterrogated"]	== true)
	{
		return true;
	}
	else 
		return false;
}

bool Notebook::danCanAccuse()
{
	if(this->gameFlags["danInterrogated"] 	== true	&&
		 this->gameFlags["vinceCleared"] 			== true	&&
		 this->gameFlags["carlCleared"] 			== true)
	{
		return true;
	}
	else 
		return false;
}

bool Notebook::royCanInterrogate()
{
	if(this->gameFlags["royRecordingAsk"] == true	&&
		 this->gameFlags["royCashAsk"] 			== true)
	{
		return true;
	}
	else 
		return false;
}

bool Notebook::louiseCanInterrogate()
{
	if(this->featureInspected["table"]					== true	&&
		 this->gameFlags["louiseLettersAsk"]			== true	&&
		 this->gameFlags["louiseSpreadsheetAsk"]	== true	&&
		 this->gameFlags["louiseFlutesAsk"]				== true)
	{
		return true;
	}
	else 
		return false;
}


bool Notebook::herbertCanInterrogate()
{
	if(this->gameFlags["herbertWrenchAsk"]	== true	&&
		 this->gameFlags["herbertReceiptAsk"] == true	&&
		 this->gameFlags["herbertAmmoniaAsk"]	== true)
	{
		return true;
	}
	else 
		return false;
}


/*******************************************************************************
*		PRINT
*******************************************************************************/

void Notebook::printGameFlags()
{
	  std::cout << "Gameflags:" << std::endl;
		
  for ( auto it = gameFlags.begin(); it != gameFlags.end(); ++it )
    std::cout << " " << it->first << ":" << it->second << std::endl;
  
	std::cout << std::endl;
}

void Notebook::printAll()
{
	
	std::cout << "Gameflags:" << std::endl;
		
  for ( auto it = gameFlags.begin(); it != gameFlags.end(); ++it )
    std::cout << " " << it->first << ":" << it->second << std::endl;
  
	std::cout << std::endl;
	
	
	std::cout << "itemLocations:" << std::endl;
		
  for ( auto it = itemLocations.begin(); it != itemLocations.end(); ++it )
    std::cout << " " << it->first << ":" << it->second << std::endl;
  
	std::cout << std::endl;

	
	std::cout << "itemAvailable:" << std::endl;
		
  for ( auto it = itemAvailable.begin(); it != itemAvailable.end(); ++it )
    std::cout << " " << it->first << ":" << it->second << std::endl;
  
	std::cout << std::endl;
	
	std::cout << "itemAnalyzed:" << std::endl;
		
  for ( auto it = itemAnalyzed.begin(); it != itemAnalyzed.end(); ++it )
    std::cout << " " << it->first << ":" << it->second << std::endl;
  
	std::cout << std::endl;

	std::cout << "featureInspected:" << std::endl;
		
  for ( auto it = featureInspected.begin(); it != featureInspected.end(); ++it )
    std::cout << " " << it->first << ":" << it->second << std::endl;
  
	std::cout << std::endl;	
	
	std::cout << "featureActioned:" << std::endl;
		
  for ( auto it = featureActioned.begin(); it != featureActioned.end(); ++it )
    std::cout << " " << it->first << ":" << it->second << std::endl;
  
	std::cout << std::endl;		
	
	std::cout << "playerLocation: " << this->playerLocation << std::endl;
  
	std::cout << std::endl;		
	
	
	
	
}
